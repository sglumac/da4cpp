[![Actions Status](https://github.com/sglumac/da4cpp/workflows/Ubuntu/badge.svg)](https://github.com/sglumac/da4cpp/actions)
[![Documentation](https://github.com/sglumac/da4cpp/actions/workflows/documentation.yaml/badge.svg)](https://github.com/sglumac/da4cpp/actions/workflows/documentation.yaml)
[![codecov](https://codecov.io/gh/sglumac/da4cpp/branch/master/graph/badge.svg)](https://codecov.io/gh/sglumac/da4cpp)

# da4cpp - Dependency Analysis for C++

**da4cpp** (Dependency Analysis for C++) is an application based on [libclang](https://clang.llvm.org/docs/LibClang.html) designed to analyze dependencies in C++ code. Its primary goal is to produce a dependency graph that helps developers visualize relationships between different components of their C++ projects.

## Features

- Parses C++ source and header files
- Extracts and visualizes dependencies between classes, functions, and modules
- Generates dependency graphs
- Supports customizable output formats
- Helps in identifying cyclic dependencies and unused code

## Installation

To use **da4cpp**, you can clone the repository and build it from source:

```sh
git clone https://github.com/sglumac/da4cpp.git
cd da4cpp
mkdir build && cd build
cmake ..
make
```

## Usage

Once built, you can use **da4cpp** to analyze a C++ project by running:

```sh
./da4cpp <source-directory>
```

### Command-line Options

- `-o <output-file>`: Specify an output file for the generated dependency report.
- `-f <format>`: Choose an output format (e.g., JSON, Graphviz).
- `-v`: Enable verbose mode for detailed analysis.

## Example

```sh
./da4cpp ./my_project -o dependencies.json -f json
./da4cpp ./my_project -o dependencies.html -f html
```

This command analyzes the `my_project` directory and saves the dependency report in JSON format.

## Output Formats

**da4cpp** supports multiple output formats:
- **JSON**: Structured format for programmatic analysis
- **Graphviz (DOT)**: Useful for visualizing dependencies as graphs
- **Plain text**: Human-readable summary

## Contributing

Contributions are welcome! To contribute:
1. Fork the repository
2. Create a new branch (`git checkout -b feature-name`)
3. Commit your changes (`git commit -m "Add new feature"`)
4. Push to the branch (`git push origin feature-name`)
5. Open a pull request

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For questions, issues, or suggestions, please create an issue on the [GitHub repository](https://github.com/sglumac/da4cpp/issues).

