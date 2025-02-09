#include <cstddef>
#include <da4cpp/parsing.hpp>
#include <iostream>
#include <optional>
#include <span>

int main(int argc, char **argv) {
  const std::span<char *> args(argv, static_cast<size_t>(argc));
  if (argc != 2) {
    std::cerr << "Usage: " << args[0] << " <source-file>" << std::endl;
    return 1;
  }

  const std::optional<da4cpp::graph::DependencyGraph> symbolInfo = da4cpp::parsing::parse_translation_unit(args[1]);

  return symbolInfo.has_value() ? 0 : 1;
}
