#ifndef DA4CPP_PARSING_H
#define DA4CPP_PARSING_H

#include <da4cpp/graph.hpp>
#include <filesystem>
#include <optional>

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
  std::optional<graph::DependencyGraph> parse_translation_unit(const std::filesystem::path &path);

}  // namespace da4cpp::parsing

#endif  // DA4CPP_PARSING_H
