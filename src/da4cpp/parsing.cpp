/**
 * @file parsing.cpp
 * @brief Implements parsing functionality using libclang to construct and traverse a dependency graph.
 */

#include <clang-c/CXFile.h>
#include <clang-c/CXSourceLocation.h>
#include <clang-c/CXString.h>
#include <clang-c/Index.h>

#include <da4cpp/graph.hpp>
#include <da4cpp/parsing.hpp>
#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

/**
 * @namespace da4cpp::graph
 * @brief Contains classes and types related to dependency graphs.
 */
using da4cpp::graph::Dependencies;
using da4cpp::graph::DependencyGraph;
using da4cpp::graph::Symbol;
using da4cpp::graph::SymbolType;

/**
 * @brief Represents a Symbol and its associated Dependencies.
 */
using SymbolAndDependencies = std::pair<Symbol, Dependencies>;

namespace {

  /**
   * @brief Defines a function pointer type for conditions that determine whether a Clang cursor should be processed.
   * @param cursor The Clang cursor to evaluate.
   * @return True if the cursor meets the condition, false otherwise.
   */
  using ProcessingCondition = bool (*)(const CXCursor &);

  /**
   * @brief Defines a function pointer type for processing a Clang cursor and extracting its symbol and dependencies.
   * @param cursor The Clang cursor to process.
   * @return A pair containing the extracted Symbol and its Dependencies.
   */
  using CursorProcessor = SymbolAndDependencies (*)(const CXCursor &);

  /**
   * @brief A tuple tying together a ProcessingCondition and its corresponding CursorProcessor.
   */
  using CursorHandler = std::tuple<ProcessingCondition, CursorProcessor>;

  /**
   * @brief A collection of CursorHandlers.
   */
  using CursorHandlers = std::vector<CursorHandler>;

  /**
   * @brief Converts a CXString to a std::string and disposes of the CXString.
   * @param cxStr The CXString to convert.
   * @return The converted std::string.
   */
  std::string to_string(CXString cxStr) {
    std::string str = clang_getCString(cxStr);
    clang_disposeString(cxStr);
    return str;
  }

  /**
   * @brief Retrieves the spelling (name) of the symbol pointed to by the given Clang cursor.
   * @param cursor The Clang cursor.
   * @return The spelled-out name of the symbol.
   */
  std::string get_symbol_name(const CXCursor &cursor) { return to_string(clang_getCursorSpelling(cursor)); }

  /**
   * @brief Constructs a Symbol from a Clang cursor and a symbol name.
   * @param cursor The Clang cursor.
   * @param symbolName The name of the symbol.
   * @param symbolType The type of the symbol.
   * @return A Symbol with file path, line, column, name, and type information.
   */
  Symbol from_cursor_and_name(const CXCursor &cursor, const std::string &symbolName, SymbolType symbolType) {
    const CXSourceLocation location = clang_getCursorLocation(cursor);
    CXFile file = nullptr;
    unsigned line = 0;
    unsigned column = 0;
    unsigned offset = 0;

    clang_getFileLocation(location, &file, &line, &column, &offset);

    return {.filePath = std::filesystem::path(to_string(clang_getFileName(file))),
            .line = line,
            .column = column,
            .name = symbolName,
            .symbolType = symbolType};
  }

  /**
   * @brief Constructs a Symbol from a Clang cursor.
   * @param cursor The Clang cursor.
   * @param symbolType The type of the symbol.
   * @return A Symbol populated with relevant cursor-based data.
   */
  Symbol from_cursor(const CXCursor &cursor, SymbolType symbolType) {
    return from_cursor_and_name(cursor, get_symbol_name(cursor), symbolType);
  }

  /**
   * @brief Constructs a Symbol representing a function declaration from a Clang cursor.
   * @param cursor The Clang cursor.
   * @return A Symbol with FunctionDeclaration type.
   */
  Symbol function_declaration_from_cursor(const CXCursor &cursor) {
    return from_cursor(cursor, SymbolType::FunctionDeclaration);
  }

  /**
   * @brief Constructs a Symbol representing a function definition from a Clang cursor.
   * @param cursor The Clang cursor.
   * @return A Symbol with FunctionDefinition type.
   */
  Symbol function_definition_from_cursor(const CXCursor &cursor) {
    return from_cursor(cursor, SymbolType::FunctionDefinition);
  }

  /**
   * @brief Checks if a cursor refers to a struct definition.
   * @param cursor The Clang cursor.
   * @return True if the cursor is a struct definition, false otherwise.
   */
  bool is_struct_definition(const CXCursor &cursor) {
    return clang_getCursorKind(cursor) == CXCursor_StructDecl && static_cast<bool>(clang_isCursorDefinition(cursor));
  }

  /**
   * @brief Checks if a cursor refers to a struct declaration (not a definition).
   * @param cursor The Clang cursor.
   * @return True if the cursor is a struct declaration, false otherwise.
   */
  bool is_struct_declaration(const CXCursor &cursor) {
    return clang_getCursorKind(cursor) == CXCursor_StructDecl && !static_cast<bool>(clang_isCursorDefinition(cursor));
  }

  /**
   * @brief Creates a Symbol representing either a type declaration or definition from the cursor.
   * @param cursor The Clang cursor.
   * @return The Symbol representing the type.
   */
  Symbol type_declaration_from_cursor(const CXCursor &cursor) {
    const bool isDefinition{static_cast<bool>(clang_isCursorDefinition(cursor))};
    const SymbolType type = isDefinition ? SymbolType::TypeDefinition : SymbolType::TypeDeclaration;
    return from_cursor(cursor, type);
  }

  /**
   * @brief Creates a Symbol representing a type definition from the cursor.
   * @param cursor The Clang cursor.
   * @return The Symbol of type TypeDefinition.
   */
  Symbol type_definition_from_cursor(const CXCursor &cursor) { return from_cursor(cursor, SymbolType::TypeDefinition); }

  /**
   * @brief Processes a struct declaration cursor to build a SymbolAndDependencies pair.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with a Symbol representing the struct declaration and no dependencies.
   */
  SymbolAndDependencies process_struct_declaration(const CXCursor &cursor) {
    const Symbol definition = type_declaration_from_cursor(cursor);
    const Dependencies dependencies{};
    return {definition, dependencies};
  }

  /**
   * @brief Checks if a cursor references a struct (via DeclRefExpr, TypeRef, or MemberRefExpr).
   * @param cursor The Clang cursor.
   * @return True if the cursor references a struct, false otherwise.
   */
  bool is_struct_reference(const CXCursor &cursor) {
    const CXCursorKind cursorKind = clang_getCursorKind(cursor);
    return (cursorKind == CXCursor_DeclRefExpr || cursorKind == CXCursor_TypeRef
            || cursorKind == CXCursor_MemberRefExpr)
           && clang_getCursorKind(clang_getCursorReferenced(cursor)) == CXCursor_StructDecl;
  }

  /**
   * @brief A visitor function to collect dependencies when visiting a struct definition.
   * @param cursor The current cursor.
   * @param parent The parent cursor (unused).
   * @param clientData Pointer to a Dependencies object used to store detected references.
   * @return CXChildVisit_Recurse to continue traversing child cursors.
   */
  // NOLINTNEXTLINE(misc-unused-parameters,bugprone-easily-swappable-parameters)
  CXChildVisitResult visit_struct_definition(CXCursor cursor, [[maybe_unused]] CXCursor parent,
                                             CXClientData clientData) {
    auto &dependencies = *static_cast<Dependencies *>(clientData);
    if (is_struct_reference(cursor)) {
      const Symbol referenced{type_declaration_from_cursor(clang_getCursorReferenced(cursor))};
      dependencies.emplace(referenced);
    }
    return CXChildVisit_Recurse;
  }

  /**
   * @brief Processes a struct definition cursor to build a SymbolAndDependencies pair.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with a Symbol representing the struct definition and any dependencies.
   */
  SymbolAndDependencies process_struct_definition(const CXCursor &cursor) {
    const Symbol definition = type_definition_from_cursor(cursor);
    Dependencies dependencies{};
    clang_visitChildren(cursor, visit_struct_definition, &dependencies);
    return {definition, dependencies};
  }

  /**
   * @brief Checks if a cursor refers to a function declaration (without definition).
   * @param cursor The Clang cursor.
   * @return True if the cursor is a function declaration, false otherwise.
   */
  bool is_function_declaration(const CXCursor &cursor) {
    return clang_getCursorKind(cursor) == CXCursor_FunctionDecl && !static_cast<bool>(clang_isCursorDefinition(cursor));
  }

  /**
   * @brief Processes a function declaration cursor, capturing its Symbol and linking to the corresponding definition.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with the function declaration as the primary symbol and its definition as a
   * dependency.
   */
  SymbolAndDependencies process_function_declaration(const CXCursor &cursor) {
    const Symbol declaration{function_declaration_from_cursor(cursor)};
    const Dependencies dependencies{};
    return {declaration, dependencies};
  }

  /**
   * @brief Checks if a cursor references a function (via DeclRefExpr or CallExpr).
   * @param cursor The Clang cursor.
   * @return True if the cursor references a function, false otherwise.
   */
  bool is_function_reference(const CXCursor &cursor) {
    const CXCursorKind cursorKind = clang_getCursorKind(cursor);
    const CXCursor referenced = clang_getCursorReferenced(cursor);

    return (cursorKind == CXCursor_DeclRefExpr || cursorKind == CXCursor_CallExpr)
           && (clang_Cursor_isNull(referenced) == 0) && clang_getCursorKind(referenced) == CXCursor_FunctionDecl;
  }

  /**
   * @brief Checks if a cursor refers to a function definition.
   * @param cursor The Clang cursor.
   * @return True if the cursor is a function definition, false otherwise.
   */
  bool is_function_definition(const CXCursor &cursor) {
    return clang_getCursorKind(cursor) == CXCursor_FunctionDecl && static_cast<bool>(clang_isCursorDefinition(cursor));
  }

  /**
   * @brief A visitor function to collect dependencies (function calls, struct references) when visiting a function
   * definition.
   * @param cursor The current cursor.
   * @param parent The parent cursor (unused).
   * @param clientData Pointer to a Dependencies object used to store detected references.
   * @return CXChildVisit_Recurse to continue traversing child cursors.
   */
  // NOLINTNEXTLINE(misc-unused-parameters,bugprone-easily-swappable-parameters)
  CXChildVisitResult visit_function_definition(CXCursor cursor, [[maybe_unused]] CXCursor parent,
                                               CXClientData clientData) {
    auto &dependencies = *static_cast<Dependencies *>(clientData);
    const CXCursor referenced = clang_getCursorReferenced(cursor);
    if (is_function_reference(cursor)) {
      if (is_function_definition(referenced)) {
        dependencies.emplace(function_definition_from_cursor(referenced));
      }
    } else if (is_struct_reference(cursor)) {
      dependencies.emplace(type_definition_from_cursor(referenced));
    }
    return CXChildVisit_Recurse;
  }

  /**
   * @brief Processes a function definition cursor to build a SymbolAndDependencies pair.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with a Symbol representing the function definition and any dependencies.
   */
  SymbolAndDependencies process_function_definition(const CXCursor &cursor) {
    const Symbol definition = function_definition_from_cursor(cursor);
    Dependencies dependencies{};
    clang_visitChildren(cursor, visit_function_definition, &dependencies);
    return {definition, dependencies};
  }

  /**
   * @brief A recursive function to traverse the AST and process relevant cursors.
   *
   * This function determines if a Clang cursor satisfies any of the known conditions (function definition, function
   * declaration, struct declaration, struct definition) and processes it accordingly.
   * @param cursor The current Clang cursor.
   * @param parent The parent cursor (unused).
   * @param clientData Pointer to a DependencyGraph object used to accumulate information.
   * @return CXChildVisit_Recurse to continue traversing child cursors.
   */
  // NOLINTNEXTLINE(misc-unused-parameters,bugprone-easily-swappable-parameters)
  CXChildVisitResult visit_node(CXCursor cursor, [[maybe_unused]] CXCursor parent, CXClientData clientData) {
    const CursorHandlers handlers{{{is_function_definition, process_function_definition},
                                   {is_function_declaration, process_function_declaration},
                                   {is_struct_declaration, process_struct_declaration},
                                   {is_struct_definition, process_struct_definition}}};

    auto *graph = static_cast<DependencyGraph *>(clientData);

    for (auto [condition, processor] : handlers) {
      if (condition(cursor)) {
        graph->emplace(processor(cursor));
        break;
      }
    }

    return CXChildVisit_Recurse;
  }
}  // namespace

/// \brief Contains parsing functions for da4cpp.
namespace da4cpp::parsing {

  /**
   * @brief Parses a translation unit to construct a dependency graph of symbols and their relationships.
   *
   * This function uses libclang to parse a source file. It creates a Clang translation unit, obtains the root cursor,
   * and visits children to build up a dependency graph capturing information about functions, structs, and their
   * interdependencies.
   *
   * @param path The filesystem path to the source file.
   * @return An optional DependencyGraph. If parsing fails, returns an empty optional.
   */
  std::optional<graph::DependencyGraph> parse_translation_unit(const std::filesystem::path &path) {
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit
        = clang_parseTranslationUnit(index, path.c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None);

    if (unit == nullptr) {
      std::cerr << "Unable to parse translation unit!" << std::endl;
      return {};
    }

    graph::DependencyGraph graph{};

    const CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(cursor, visit_node, &graph);

    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
    return graph;
  }

}  // namespace da4cpp::parsing
