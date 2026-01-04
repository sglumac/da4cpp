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
#include <da4cpp/parsing/handlers.hpp>
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
    auto *graph = static_cast<DependencyGraph *>(clientData);

    for (auto [condition, processor] : da4cpp::parsing::handlers::cursorHandlers) {
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
