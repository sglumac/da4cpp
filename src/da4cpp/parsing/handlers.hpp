#ifndef DA4CPP_PARSING_HANDLERS_H
#define DA4CPP_PARSING_HANDLERS_H

#include <clang-c/Index.h>
#include <array>
#include <da4cpp/graph.hpp>
#include <da4cpp/parsing/filters.hpp>
#include <da4cpp/parsing/processors.hpp>

namespace da4cpp::parsing::handlers {

  /**
   * @brief Function pointer type that determines whether a Clang cursor should be processed.
   * @param cursor The Clang cursor to evaluate.
   * @return True if the cursor meets the condition, false otherwise.
   */
  using CursorFilter = bool (*)(const CXCursor &);

  /**
   * @brief Function pointer type for processing a Clang cursor and extracting its symbol and dependencies.
   * @param cursor The Clang cursor to process.
   * @return A pair containing the extracted Symbol and its Dependencies.
   */
  using CursorProcessor = processors::SymbolAndDependencies (*)(const CXCursor &);

  /**
   * @brief A struct that handles Clang cursors of a specific type.
   */
  struct CursorHandler {
    CursorFilter filter; ///< Determines if a cursor should be processed.
    CursorProcessor processor; ///< Processes the cursor if the filter returns true.
  };

  /**
   * @brief A collection of CursorHandlers.
   */
  inline constexpr auto cursorHandlers = std::to_array<CursorHandler>({
         {.filter=filters::is_function_definition, .processor=processors::process_function_definition},
         {.filter=filters::is_function_declaration, .processor=processors::process_function_declaration},
         {.filter=filters::is_struct_declaration, .processor=processors::process_struct_declaration},
         {.filter=filters::is_struct_definition, .processor=processors::process_struct_definition}});

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
  CXChildVisitResult visit_node(CXCursor cursor, [[maybe_unused]] CXCursor parent, CXClientData clientData);
}  // namespace da4cpp::parsing::handlers

#endif // DA4CPP_PARSING_HANDLERS_H


