
.. _program_listing_file_src_da4cpp_parsing.hpp:

Program Listing for File parsing.hpp
====================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_da4cpp_parsing.hpp>` (``src/da4cpp/parsing.hpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include <da4cpp/graph.hpp>
   #include <filesystem>
   #include <optional>
   
   #ifndef DA4CPP_PARSING_H
   #  define DA4CPP_PARSING_H
   
   namespace da4cpp::parsing {
   
     std::optional<graph::DependencyGraph> parse_translation_unit(const std::filesystem::path &path);
   
   }  // namespace da4cpp::parsing
   
   #endif  // DA4CPP_PARSING_H
