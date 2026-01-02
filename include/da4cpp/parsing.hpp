#ifndef DA4CPP_PARSING_H
#define DA4CPP_PARSING_H

#include <da4cpp/graph.hpp>
#include <filesystem>
#include <optional>

namespace da4cpp::parsing {

  std::optional<graph::DependencyGraph> parse_translation_unit(const std::filesystem::path &path);

}  // namespace da4cpp::parsing

#endif  // DA4CPP_PARSING_H
