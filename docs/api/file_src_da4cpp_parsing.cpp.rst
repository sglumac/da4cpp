
.. _file_src_da4cpp_parsing.cpp:

File parsing.cpp
================

|exhale_lsh| :ref:`Parent directory <dir_src_da4cpp>` (``src/da4cpp``)

.. |exhale_lsh| unicode:: U+021B0 .. UPWARDS ARROW WITH TIP LEFTWARDS



Implements parsing functionality using libclang to construct and traverse a dependency graph. 



.. contents:: Contents
   :local:
   :backlinks: none

Definition (``src/da4cpp/parsing.cpp``)
---------------------------------------


.. toctree::
   :maxdepth: 1

   program_listing_file_src_da4cpp_parsing.cpp.rst





Includes
--------


- ``clang-c/CXFile.h``

- ``clang-c/CXSourceLocation.h``

- ``clang-c/CXString.h``

- ``clang-c/Index.h``

- ``da4cpp/graph.hpp`` (:ref:`file_src_da4cpp_graph.hpp`)

- ``da4cpp/parsing.hpp`` (:ref:`file_src_da4cpp_parsing.hpp`)

- ``filesystem``

- ``iostream``

- ``optional``

- ``string``

- ``tuple``

- ``utility``

- ``vector``






Namespaces
----------


- :ref:`namespace_anonymous_namespace{parsing.cpp}`

- :ref:`namespace_da4cpp`

- :ref:`namespace_da4cpp__graph`

- :ref:`namespace_da4cpp__parsing`


Functions
---------


- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1af79e03782424be4e1a517055707cd279`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a25f53986484be2ac058c92250f530903`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ae92d161dbb289c3c10e758429f4b7474`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a818da856d671a2d0ca81b2f95f3dfb19`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ac430d3ad690250bf8698fab850116d7d`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a76127554ea719311c60dbcfb5b0658fe`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1adf80a2f5cae79ba4804a25cda160a0b2`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1abab7bd0f0109068ff38de441e1744d81`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a8bf92ac02f27af018c01f386dff0da61`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a0f6c6e5cc86c194419253e8785fd796c`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a0aadd31ac60a10d17fa33a165798ba0a`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ace99474350c6495751d9fdfd956c103c`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a27ae436fd9b015a24e644bbde3fe1d7e`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a5e5476668f221690a8cbd6cf344ea16d`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a2d8978993a237d43d6cf4e89bbd6954e`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a2e5f4d2119d474a411999a56e841362f`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ae5ca2ed8d8b036fa670fea524f681b78`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1aef45c84c2b40d344682f0914cc3ed8da`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a97f9c426f6f9d16ec04104bbeac1db3c`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1aeb5e295d5faa38a298f59077b4879cf5`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a8535e931bdbe5a7de0c19059f659d7e5`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1af79e03782424be4e1a517055707cd279`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a25f53986484be2ac058c92250f530903`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ae92d161dbb289c3c10e758429f4b7474`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a818da856d671a2d0ca81b2f95f3dfb19`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ac430d3ad690250bf8698fab850116d7d`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a76127554ea719311c60dbcfb5b0658fe`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1adf80a2f5cae79ba4804a25cda160a0b2`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1abab7bd0f0109068ff38de441e1744d81`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a8bf92ac02f27af018c01f386dff0da61`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a0f6c6e5cc86c194419253e8785fd796c`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a0aadd31ac60a10d17fa33a165798ba0a`

- :ref:`exhale_function_namespaceda4cpp_1_1parsing_1a6fe77e69e4cc733f83016edfd139ca81`

- :ref:`exhale_function_namespaceda4cpp_1_1parsing_1a6fe77e69e4cc733f83016edfd139ca81`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ace99474350c6495751d9fdfd956c103c`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a27ae436fd9b015a24e644bbde3fe1d7e`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a5e5476668f221690a8cbd6cf344ea16d`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a2d8978993a237d43d6cf4e89bbd6954e`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a2e5f4d2119d474a411999a56e841362f`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1ae5ca2ed8d8b036fa670fea524f681b78`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1aef45c84c2b40d344682f0914cc3ed8da`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a97f9c426f6f9d16ec04104bbeac1db3c`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1aeb5e295d5faa38a298f59077b4879cf5`

- :ref:`exhale_function_namespaceanonymous__namespace_02parsing_8cpp_03_1a8535e931bdbe5a7de0c19059f659d7e5`


Typedefs
--------


- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1aed5ae99d86440861c2cc2e3e5fd9203e`

- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1a7b75726b88e5d9d4902a0b12b87e5d2e`

- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1abb4249e465d3a45d17b921914d466c08`

- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1a1a4b4d96d5ebb0f33aec9115c9d9b198`

- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1aed5ae99d86440861c2cc2e3e5fd9203e`

- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1a7b75726b88e5d9d4902a0b12b87e5d2e`

- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1abb4249e465d3a45d17b921914d466c08`

- :ref:`exhale_typedef_namespaceanonymous__namespace_02parsing_8cpp_03_1a1a4b4d96d5ebb0f33aec9115c9d9b198`

- :ref:`exhale_typedef_parsing_8cpp_1ac4f2e381856feec24d9d9df051e5be20`

