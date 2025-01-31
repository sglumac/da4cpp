struct B;

struct A {
  B* bptr;
};

struct B {
  A* aptr;
};

int main() {
  A a{};
  B b{};
  a.bptr = &b;
  b.aptr = &a;

  return 0;
}
