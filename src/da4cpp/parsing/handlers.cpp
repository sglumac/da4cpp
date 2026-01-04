#include <clang-c/CXFile.h>
#include <clang-c/CXSourceLocation.h>
#include <clang-c/CXString.h>
#include <clang-c/Index.h>

#include <da4cpp/parsing/filters.hpp>
#include <da4cpp/parsing/handlers.hpp>


namespace da4cpp::parsing::handlers {

  // NOLINTNEXTLINE(misc-unused-parameters,bugprone-easily-swappable-parameters)
  CXChildVisitResult visit_node(CXCursor cursor, [[maybe_unused]] CXCursor parent, CXClientData clientData) {

    auto *graph = static_cast<graph::DependencyGraph *>(clientData);

    for (auto [condition, processor] : da4cpp::parsing::handlers::cursorHandlers) {
      if (condition(cursor)) {
        graph->emplace(processor(cursor));
        break;
      }
    }

    return CXChildVisit_Recurse;
  }
} // namespace da4cpp::parsing::handlers

