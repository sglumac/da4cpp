#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <da4cpp/parsing.hpp>
#include <filesystem>
#include <map>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>

using da4cpp::graph::DependencyGraph;
using da4cpp::graph::Dependencies;
using da4cpp::graph::Symbol;
using da4cpp::graph::SymbolType;
using da4cpp::parsing::parse_translation_unit;

struct SymbolMatch {
  std::string filepath;
  SymbolType symbolType;
  std::string name;
  bool operator()(const Symbol &symbol) const {
    return symbol.filePath == filepath && symbol.name == name && symbol.symbolType == symbolType;
  }
};

namespace {

std::filesystem::path resources_dir() { return std::filesystem::path{ TEST_BINARY_DIR } / "parsing.tests.resources"; }

using TestParameters = std::tuple<std::filesystem::path, DependencyGraph>;

std::ostream& operator<<(std::ostream& oss, const Symbol& symbol) {
  const std::map<SymbolType, std::string> representation{
      {SymbolType::TypeDefinition, "TypeDefinition"},
      {SymbolType::TypeDeclaration, "TypeDeclaration"},
      {SymbolType::FunctionDefinition, "FunctionDefinition"},
      {SymbolType::FunctionDeclaration, "FunctionDeclaration"},
      {SymbolType::VariableDefinition, "VariableDefinition"},
      {SymbolType::VariableDeclaration, "VariableDeclaration"}
  };

  oss << symbol.name << " - " << representation.at(symbol.symbolType) << " (" << symbol.filePath.filename().string() << ":" << symbol.line << "," << symbol.column << ")";
  return oss;
}

std::ostream& operator<<(std::ostream& oss, const Dependencies& dependencies) {
  oss << "{";
  for (auto it = dependencies.begin(); it != dependencies.end(); ++it) {
    if (it != dependencies.begin()) {
      oss << ", ";
    }
    oss << *it;
  }
  oss << "}";
  return oss;
}

std::string compare_maps(const DependencyGraph& actual, const DependencyGraph& expected) {
    std::ostringstream oss;
    for (const auto& [symbol, dependencies] : actual) {
        if (!expected.contains(symbol)) {
          oss << "Extra symbol in actual" << std::endl
              << symbol << std::endl
              << "with dependencies" << std::endl
              << dependencies << std::endl;
        } else if (expected.at(symbol) != dependencies) {
            oss << "Mismatched dependencies for symbol " << std::endl
                << symbol << std::endl
                << "where actual =" << std::endl
                << dependencies << std::endl
                << "and expected = " << std::endl
                << expected.at(symbol) << std::endl;
        }
    }

    for (const auto& [symbol, dependencies] : expected) {
        if (!actual.contains(symbol)) {
            oss << "Missing symbol in actual" << std::endl
                << symbol << std::endl
                << "with dependencies" << std::endl
                << dependencies << std::endl;
        }
    }

    return oss.str();
}

void check_dependency_graph(const std::filesystem::path& resourcePath, const DependencyGraph& expectedGraph) {

  std::optional<DependencyGraph> graphOption = parse_translation_unit(resourcePath);

  if (graphOption.has_value()) {
    const DependencyGraph& actualGraph = graphOption.value();
    INFO(compare_maps(actualGraph, expectedGraph));
    REQUIRE(expectedGraph == actualGraph);
  } else {
    FAIL("parse_translation_unit failed to parse" + resourcePath.string());
  }
}

auto get_symbol_constructor(const std::filesystem::path& resourcePath) {
  return [resourcePath](unsigned int line, unsigned int column, const std::string &name, SymbolType symbolType) {
    return Symbol{.filePath = resourcePath, .line = line, .column = column, .name = name, .symbolType = symbolType};
  };
}
}  // namespace

TEST_CASE("function_call") {
  const std::filesystem::path resourcePath{resources_dir() / "function_call.cpp"};
  auto symbol = get_symbol_constructor(resourcePath);

  const Symbol functionDeclaration{symbol(1, 6, "function", SymbolType::FunctionDeclaration)};
  const Symbol functionDefinition{symbol(8, 6, "function", SymbolType::FunctionDefinition)};
  const Symbol mainDefinition{symbol(3, 5, "main", SymbolType::FunctionDefinition)};

  const DependencyGraph expectedGraph  {
      {functionDeclaration, {functionDefinition}},
      {functionDefinition, {}},
      {mainDefinition, {functionDeclaration}}
  };

  check_dependency_graph(resourcePath, expectedGraph);
}

TEST_CASE("struct_reference") {
  const std::filesystem::path resourcePath{resources_dir() / "struct_reference.cpp"};
  auto symbol = get_symbol_constructor(resourcePath);

  const Symbol structDefinition{symbol(1, 8, "Structure", SymbolType::TypeDefinition)};
  const Symbol mainDefinition{symbol(5, 5, "main", SymbolType::FunctionDefinition)};

  const DependencyGraph expectedGraph  {
        {structDefinition, {}},
        {mainDefinition, {structDefinition}}
  };

  check_dependency_graph(resourcePath, expectedGraph);
}

TEST_CASE("cyclic_struct_dependency") {
  const std::filesystem::path resourcePath{resources_dir() / "cyclic_struct_dependency.cpp"};
  auto symbol = get_symbol_constructor(resourcePath);

  const Symbol definitionA{symbol(3, 8, "A", SymbolType::TypeDefinition)};
  const Symbol definitionB{symbol(7, 8, "B", SymbolType::TypeDefinition)};
  const Symbol declarationB{symbol(1, 8, "B", SymbolType::TypeDeclaration)};
  const Symbol mainDefinition{symbol(11, 5, "main", SymbolType::FunctionDefinition)};

  const DependencyGraph expectedGraph  {
        {definitionA, {declarationB}},
        {definitionB, {definitionA}},
        {declarationB, {}},
        {mainDefinition, {definitionA, definitionB}}
  };

  check_dependency_graph(resourcePath, expectedGraph);
}

