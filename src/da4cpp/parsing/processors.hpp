#ifndef DA4CPP_PARSING_HANDLERS_PROCESSORS_H
#define DA4CPP_PARSING_HANDLERS_PROCESSORS_H

#include <clang-c/Index.h>
#include <da4cpp/graph.hpp>

namespace da4cpp::parsing::handlers::processors {
  using da4cpp::graph::Dependencies;
  using da4cpp::graph::DependencyGraph;
  using da4cpp::graph::Symbol;
  using da4cpp::graph::SymbolType;

  /**
   * @brief Represents a Symbol and its associated Dependencies.
   */
  using SymbolAndDependencies = std::pair<da4cpp::graph::Symbol, da4cpp::graph::Dependencies>;

  /**
   * @brief Processes a struct declaration cursor to build a SymbolAndDependencies pair.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with a Symbol representing the struct declaration and no dependencies.
   */
  SymbolAndDependencies process_struct_declaration(const CXCursor &cursor);

  /**
   * @brief Processes a struct definition cursor to build a SymbolAndDependencies pair.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with a Symbol representing the struct definition and any dependencies.
   */
  SymbolAndDependencies process_struct_definition(const CXCursor &cursor);

  /**
   * @brief Processes a function declaration cursor, capturing its Symbol and linking to the corresponding definition.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with the function declaration as the primary symbol and its definition as a
   * dependency.
   */
  SymbolAndDependencies process_function_declaration(const CXCursor &cursor);

  /**
   * @brief Processes a function definition cursor to build a SymbolAndDependencies pair.
   * @param cursor The Clang cursor.
   * @return A SymbolAndDependencies with a Symbol representing the function definition and any dependencies.
   */
  SymbolAndDependencies process_function_definition(const CXCursor &cursor);

}  // namespace da4cpp::parsing::handlers::filters

#endif // DA4CPP_PARSING_HANDLERS_PROCESSORS_H

