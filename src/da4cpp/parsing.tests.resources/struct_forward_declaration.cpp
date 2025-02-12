/// @brief Forward declaration of struct B.
struct B;

/**
 * @brief Struct A that contains a pointer to struct B.
 */
struct A {
  B* bptr;  ///< Requires only forward declaration.
};
