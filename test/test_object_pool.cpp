#include "../todoHOF-object-pool-pattern.h"
#include "test.h"

struct TestObjectPool {
  void test_constructors() {
    ObjectPool<Foo> op;
    assert_equal(op.free_indexes.size(), static_cast<size_t>(10));
    assert_equal(op.indexes_in_use.size(), static_cast<size_t>(0));
  }

  void test_operators() {}
  void test_custom_deleter() {}
};

int main(int argc, char *argv[]) {
  TestObjectPool t;
  t.test_constructors();
  t.test_operators();
  t.test_custom_deleter();
  // test_lifetime();

  test_results();
  return 0;
}
