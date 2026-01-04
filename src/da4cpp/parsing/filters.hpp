#ifndef DA4CPP_PARSING_HANDLERS_FILTERS_H
#define DA4CPP_PARSING_HANDLERS_FILTERS_H

#include <clang-c/Index.h>

namespace da4cpp::parsing::handlers::filters {

  /**
   * @brief Checks if a cursor refers to a struct definition.
   * @param cursor The Clang cursor.
   * @return True if the cursor is a struct definition, false otherwise.
   */
  bool is_struct_definition(const CXCursor &cursor);

  /**
   * @brief Checks if a cursor refers to a struct declaration (not a definition).
   * @param cursor The Clang cursor.
   * @return True if the cursor is a struct declaration, false otherwise.
   */
  bool is_struct_declaration(const CXCursor &cursor);

  /**
   * @brief Checks if a cursor references a struct (via DeclRefExpr, TypeRef, or MemberRefExpr).
   * @param cursor The Clang cursor.
   * @return True if the cursor references a struct, false otherwise.
   */
  bool is_struct_reference(const CXCursor &cursor);

  /**
   * @brief Checks if a cursor refers to a function declaration (without definition).
   * @param cursor The Clang cursor.
   * @return True if the cursor is a function declaration, false otherwise.
   */
  bool is_function_declaration(const CXCursor &cursor);

  /**
   * @brief Checks if a cursor references a function (via DeclRefExpr or CallExpr).
   * @param cursor The Clang cursor.
   * @return True if the cursor references a function, false otherwise.
   */
  bool is_function_reference(const CXCursor &cursor);

  /**
   * @brief Checks if a cursor refers to a function definition.
   * @param cursor The Clang cursor.
   * @return True if the cursor is a function definition, false otherwise.
   */
  bool is_function_definition(const CXCursor &cursor);

}  // namespace da4cpp::parsing::handlers::filters

#endif // DA4CPP_PARSING_HANDLERS_FILTERS_H

