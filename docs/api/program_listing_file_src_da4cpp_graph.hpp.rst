
.. _program_listing_file_src_da4cpp_graph.hpp:

Program Listing for File graph.hpp
==================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_da4cpp_graph.hpp>` (``src/da4cpp/graph.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include <filesystem>
   #include <map>
   #include <set>
   #include <string>
   
   #ifndef DA4CPP_GRAPH_HPP
   #  define DA4CPP_GRAPH_HPP
   
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
   
   #endif  // DA4CPP_GRAPH_HPP
