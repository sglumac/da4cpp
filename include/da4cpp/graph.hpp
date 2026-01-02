#include <filesystem>
#include <map>
#include <set>
#include <string>

#ifndef DA4CPP_GRAPH_HPP
#  define DA4CPP_GRAPH_HPP

namespace da4cpp::graph {

  /**
   * @brief Enumeration of different types of symbols in the dependency graph.
   */
  enum class SymbolType : std::uint8_t {
    FunctionDefinition,   ///< A function definition with an implementation.
    FunctionDeclaration,  ///< A function declaration without an implementation.
    TypeDeclaration,      ///< A forward declaration of a type (e.g., struct or class).
    TypeDefinition,       ///< A fully defined type (e.g., struct or class).
    VariableDeclaration,  ///< A variable declaration without initialization.
    VariableDefinition    ///< A variable definition with memory allocated or initialized.
  };

  /**
   * @brief Represents a symbol in the dependency graph.
   */
  struct Symbol {
    std::filesystem::path filePath;  ///< The path to the file where the symbol is located
    unsigned int line;               ///< The line number where the symbol is located
    unsigned int column;             ///< The column number where the symbol is located
    std::string name;                ///< The name of the symbol
    SymbolType symbolType;           ///< The type of the symbol

    /**
     * @brief Default three-way comparison operator.
     * @return std::strong_ordering indicating how this Symbol compares
     *         to the other (less, equal, or greater).
     */
    auto operator<=>(const Symbol &) const = default;
  };

  /**
   * @brief Represents a dependency between two symbols.
   */
  struct Dependency {
    const Symbol *source;  ///< The symbol that depends on another symbol
    const Symbol *target;  ///< The symbol that is depended upon by the source
  };

  /**
   * @brief Represents a set of dependencies for a given symbol.
   */
  using Dependencies = std::set<Symbol>;

  /**
   * @brief Represents a dependency graph mapping symbols to their dependencies.
   */
  using DependencyGraph = std::map<Symbol, Dependencies>;

}  // namespace da4cpp::graph

#endif  // DA4CPP_GRAPH_HPP
