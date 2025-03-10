
.. _program_listing_file_src_da4cpp_parsing.cpp:

Program Listing for File parsing.cpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_da4cpp_parsing.cpp>` (``src/da4cpp/parsing.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   
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
   
   using da4cpp::graph::Dependencies;
   using da4cpp::graph::DependencyGraph;
   using da4cpp::graph::Symbol;
   using da4cpp::graph::SymbolType;
   
   using SymbolAndDependencies = std::pair<Symbol, Dependencies>;
   
   namespace {
   
     using ProcessingCondition = bool (*)(const CXCursor &);
   
     using CursorProcessor = SymbolAndDependencies (*)(const CXCursor &);
   
     using CursorHandler = std::tuple<ProcessingCondition, CursorProcessor>;
   
     using CursorHandlers = std::vector<CursorHandler>;
   
     std::string to_string(CXString cxStr) {
       std::string str = clang_getCString(cxStr);
       clang_disposeString(cxStr);
       return str;
     }
   
     std::string get_symbol_name(const CXCursor &cursor) { return to_string(clang_getCursorSpelling(cursor)); }
   
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
   
     Symbol from_cursor(const CXCursor &cursor, SymbolType symbolType) {
       return from_cursor_and_name(cursor, get_symbol_name(cursor), symbolType);
     }
   
     Symbol function_declaration_from_cursor(const CXCursor &cursor) {
       return from_cursor(cursor, SymbolType::FunctionDeclaration);
     }
   
     Symbol function_definition_from_cursor(const CXCursor &cursor) {
       return from_cursor(cursor, SymbolType::FunctionDefinition);
     }
   
     bool is_struct_definition(const CXCursor &cursor) {
       return clang_getCursorKind(cursor) == CXCursor_StructDecl && static_cast<bool>(clang_isCursorDefinition(cursor));
     }
   
     bool is_struct_declaration(const CXCursor &cursor) {
       return clang_getCursorKind(cursor) == CXCursor_StructDecl && !static_cast<bool>(clang_isCursorDefinition(cursor));
     }
   
     Symbol type_declaration_from_cursor(const CXCursor &cursor) {
       const bool isDefinition{static_cast<bool>(clang_isCursorDefinition(cursor))};
       const SymbolType type = isDefinition ? SymbolType::TypeDefinition : SymbolType::TypeDeclaration;
       return from_cursor(cursor, type);
     }
   
     Symbol type_definition_from_cursor(const CXCursor &cursor) { return from_cursor(cursor, SymbolType::TypeDefinition); }
   
     SymbolAndDependencies process_struct_declaration(const CXCursor &cursor) {
       const Symbol definition = type_declaration_from_cursor(cursor);
       const Dependencies dependencies{};
       return {definition, dependencies};
     }
   
     bool is_struct_reference(const CXCursor &cursor) {
       const CXCursorKind cursorKind = clang_getCursorKind(cursor);
       return (cursorKind == CXCursor_DeclRefExpr || cursorKind == CXCursor_TypeRef
               || cursorKind == CXCursor_MemberRefExpr)
              && clang_getCursorKind(clang_getCursorReferenced(cursor)) == CXCursor_StructDecl;
     }
   
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
   
     SymbolAndDependencies process_struct_definition(const CXCursor &cursor) {
       const Symbol definition = type_definition_from_cursor(cursor);
       Dependencies dependencies{};
       clang_visitChildren(cursor, visit_struct_definition, &dependencies);
       return {definition, dependencies};
     }
   
     bool is_function_declaration(const CXCursor &cursor) {
       return clang_getCursorKind(cursor) == CXCursor_FunctionDecl && !static_cast<bool>(clang_isCursorDefinition(cursor));
     }
   
     SymbolAndDependencies process_function_declaration(const CXCursor &cursor) {
       const Symbol declaration{function_declaration_from_cursor(cursor)};
       const Dependencies dependencies{};
       return {declaration, dependencies};
     }
   
     bool is_function_reference(const CXCursor &cursor) {
       const CXCursorKind cursorKind = clang_getCursorKind(cursor);
       const CXCursor referenced = clang_getCursorReferenced(cursor);
   
       return (cursorKind == CXCursor_DeclRefExpr || cursorKind == CXCursor_CallExpr)
              && (clang_Cursor_isNull(referenced) == 0) && clang_getCursorKind(referenced) == CXCursor_FunctionDecl;
     }
   
     bool is_function_definition(const CXCursor &cursor) {
       return clang_getCursorKind(cursor) == CXCursor_FunctionDecl && static_cast<bool>(clang_isCursorDefinition(cursor));
     }
   
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
   
     SymbolAndDependencies process_function_definition(const CXCursor &cursor) {
       const Symbol definition = function_definition_from_cursor(cursor);
       Dependencies dependencies{};
       clang_visitChildren(cursor, visit_function_definition, &dependencies);
       return {definition, dependencies};
     }
   
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
   
   namespace da4cpp::parsing {
   
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
