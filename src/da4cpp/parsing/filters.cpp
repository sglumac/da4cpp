#include <clang-c/CXFile.h>
#include <clang-c/CXSourceLocation.h>
#include <clang-c/CXString.h>
#include <clang-c/Index.h>

#include <da4cpp/parsing/filters.hpp>

namespace da4cpp::parsing::handlers::filters {

  bool is_struct_definition(const CXCursor &cursor) {
    return clang_getCursorKind(cursor) == CXCursor_StructDecl && static_cast<bool>(clang_isCursorDefinition(cursor));
  }

  bool is_struct_declaration(const CXCursor &cursor) {
    return clang_getCursorKind(cursor) == CXCursor_StructDecl && !static_cast<bool>(clang_isCursorDefinition(cursor));
  }

  bool is_struct_reference(const CXCursor &cursor) {
    const CXCursorKind cursorKind = clang_getCursorKind(cursor);
    return (cursorKind == CXCursor_DeclRefExpr || cursorKind == CXCursor_TypeRef
            || cursorKind == CXCursor_MemberRefExpr)
           && clang_getCursorKind(clang_getCursorReferenced(cursor)) == CXCursor_StructDecl;
  }

  bool is_function_declaration(const CXCursor &cursor) {
    return clang_getCursorKind(cursor) == CXCursor_FunctionDecl && !static_cast<bool>(clang_isCursorDefinition(cursor));
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

}  // namespace da4cpp::parsing::handlers::filters
