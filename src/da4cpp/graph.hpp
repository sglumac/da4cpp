
#include <filesystem>
#include <map>
#include <set>
#include <string>

#ifndef da4cppGRAPH_HPP
# define da4cppGRAPH_HPP

namespace da4cpp::graph {

  enum class SymbolType : std::uint8_t {
    FunctionDefinition,
    FunctionDeclaration,
    TypeDeclaration,
    TypeDefinition,
    VariableDeclaration,
    VariableDefinition
  };

  struct Symbol {
    std::filesystem::path filePath;
    unsigned int line;
    unsigned int column;
    std::string name;
    SymbolType symbolType;
    auto operator<=>(const Symbol &) const = default;
  };

  struct Dependency {
    const Symbol *source;
    const Symbol *target;
  };

  using Dependencies = std::set<Symbol>;

  using DependencyGraph = std::map<Symbol, Dependencies>;

}  // namespace da4cpp::graph

#endif  // da4cppGRAPH_HPP
