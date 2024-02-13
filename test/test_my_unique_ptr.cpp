#include "../my_unique_ptr.h"
#include "test.h"

struct Foo {
  int a;
  Foo() : a{7} { cout << "creating a Foo" << endl; }
};

template <typename T> struct my_foo_deleter {
  bool *function_called_flag;
  my_foo_deleter(bool *b) : function_called_flag{b} {}
  void operator()(T *t) {
    cout << "deleting a Foo!" << endl;
    *function_called_flag = true;
    delete t;
  }
};

void test_constructors() {
  my_unique_ptr<Foo> a;
  assert(a.get() == nullptr);
  my_unique_ptr<Foo> b{new Foo};

  Foo f;
  assert_equal(sizeof(*b), sizeof(f));
}

void test_custom_deleter() {

  bool function_called_flag = false;
  {
    my_unique_ptr<Foo, my_foo_deleter<Foo>> a{
        new Foo, my_foo_deleter<Foo>{&function_called_flag}};
  }
  assert_equal(function_called_flag, true);
}

void test_move() {
  my_unique_ptr<Foo> a;
  my_unique_ptr<Foo> b{new Foo};
  a = std::move(b);
  assert(b.get() == nullptr);
  assert_equal(a->a, 7);
}

void test_operators() {
  my_unique_ptr<Foo> e{new Foo};
  assert_equal((*e).a, 7);
  assert_equal(e->a, 7);
}

void test_lifetime() {
  // actually compiler/clangd tests this for us
  { my_unique_ptr<Foo> q{new Foo}; }
  // assert_nonexists(q); // compiler caught this
}

int main(int argc, char *argv[]) {
  test_constructors();
  test_operators();
  test_move();
  test_custom_deleter();
  // test_lifetime();

  test_results();
  return 0;
}
