#include <clang-c/CXFile.h>
#include <clang-c/CXSourceLocation.h>
#include <clang-c/CXString.h>
#include <clang-c/Index.h>

#include <da4cpp/parsing/filters.hpp>
#include <da4cpp/parsing/processors.hpp>

namespace {
  using da4cpp::parsing::handlers::filters::is_function_definition;
  using da4cpp::parsing::handlers::filters::is_function_reference;
  using da4cpp::parsing::handlers::filters::is_struct_reference;
  using da4cpp::graph::Dependencies;
  using da4cpp::graph::DependencyGraph;
  using da4cpp::graph::Symbol;
  using da4cpp::graph::SymbolType;

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
   * @brief Creates a Symbol representing a type definition from the cursor.
   * @param cursor The Clang cursor.
   * @return The Symbol of type TypeDefinition.
   */
  Symbol type_definition_from_cursor(const CXCursor &cursor) { return from_cursor(cursor, SymbolType::TypeDefinition); }

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
} // namespace

namespace da4cpp::parsing::handlers::processors {

  SymbolAndDependencies process_struct_declaration(const CXCursor &cursor) {
    const Symbol definition = type_declaration_from_cursor(cursor);
    const Dependencies dependencies{};
    return {definition, dependencies};
  }


  SymbolAndDependencies process_struct_definition(const CXCursor &cursor) {
    const Symbol definition = type_definition_from_cursor(cursor);
    Dependencies dependencies{};
    clang_visitChildren(cursor, visit_struct_definition, &dependencies);
    return {definition, dependencies};
  }

  SymbolAndDependencies process_function_declaration(const CXCursor &cursor) {
    const Symbol declaration{function_declaration_from_cursor(cursor)};
    const Dependencies dependencies{};
    return {declaration, dependencies};
  }

  SymbolAndDependencies process_function_definition(const CXCursor &cursor) {
    const Symbol definition = function_definition_from_cursor(cursor);
    Dependencies dependencies{};
    clang_visitChildren(cursor, visit_function_definition, &dependencies);
    return {definition, dependencies};
  }

} // namespace da4cpp::parsing::handlers

