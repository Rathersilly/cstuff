#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename T> void print_vector(const std::vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << std::endl;
}

class Foo {
  inline static int count = 1;

public:
  int a;
  Foo() {
    a = count;
    ++count;
  }
  ~Foo() {}
};

template <typename T> class ObjectPool {

  vector<T> resources;
  vector<T *> free_resources;
  size_t max_resources;
  // vector<int> indexes_in_use;
  // vector<int> free_indexes;

public:
  friend struct TestObjectPool;
  class op_ptr {
  private:
    std::unique_ptr<T> curr;

  public:
    ~op_ptr() {}
  };
  op_ptr acquire() {
    op_ptr p;
    // move ptr from available

    ;
    ;
  }

  void free() {
    ;
    ;
  }

  ObjectPool(size_t max_res = 10) : max_resources{max_res} {
    for (int i = 0; i < max_resources; ++i) {
      T t;
      free_resources.push_back(make_unique<T>(t));
      resources.push_back(t);
    }
  }

  ~ObjectPool() {}
};

// int main() {
//   ObjectPool<Foo> op;
//   cout << "free_indexes: ";
//   print_vector(op.free_indexes);
//
//   cout << "indexes_in_use: ";
//   print_vector(op.indexes_in_use);
//   {
//     auto f = op.acquire();
//     cout << f->a << endl;
//     cout << "free_indexes: ";
//     print_vector(op.free_indexes);
//
//     cout << "indexes_in_use: ";
//     print_vector(op.indexes_in_use);
//   }
//   cout << "free_indexes: ";
//   print_vector(op.free_indexes);
//
//   cout << "indexes_in_use: ";
//   print_vector(op.indexes_in_use);
//   // get object from pool
//   // return object to pool
//   //
//   //
// }
