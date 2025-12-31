
.. _program_listing_file_src_main.cpp:

Program Listing for File main.cpp
=================================

|exhale_lsh| :ref:`Return to documentation for file <file_src_main.cpp>` (``src/main.cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS

.. code-block:: cpp

   #include <cstddef>
   #include <da4cpp/parsing.hpp>
   #include <iostream>
   #include <optional>
   #include <span>
   
   int main(int argc, char **argv) {
     const int maxArgCount = 1;
     const int failureCode = 1;
     const std::span<char *> args(argv, static_cast<size_t>(argc));
     if (argc != maxArgCount) {
       std::cerr << "Usage: " << args[0] << " <source-file>" << std::endl;
       return failureCode;
     }
   
     const std::optional<da4cpp::graph::DependencyGraph> symbolInfo = da4cpp::parsing::parse_translation_unit(args[1]);
   
     return symbolInfo.has_value() ? 0 : failureCode;
   }
