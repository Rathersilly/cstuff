#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

using namespace std;

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

  vector<T> elem;
  int max_elements;
  vector<int> indexes_in_use;
  vector<int> free_indexes;

public:
  std::unique_ptr<T, void (*)(T *)> acquire2() {
    if (free_indexes.empty()) {
      std::cerr << "no free indexes" << std::endl;
      throw std::runtime_error("pool exhausted");
    }
    int index = free_indexes.back();
    free_indexes.pop_back();
    indexes_in_use.push_back(index);

    auto deleter = [this, index](T *ptr) {
      this->free_indexes.push_back(index);

      auto stored_index = std::find(this->indexes_in_use.begin(),
                                    this->indexes_in_use.end(), index);
      if (stored_index != this->indexes_in_use.end()) {
        this->indexes_in_use.erase(stored_index);
      }
      delete ptr;
    };

    return std::unique_ptr<T, void (*)(T *)>(elem[index], deleter);
  }

  ObjectPool(int max_elem = 10) : max_elements{max_elem} {
    for (int i = 0; i < max_elements; ++i) {
      free_indexes.push_back(i);
      T t;
      elem.push_back(t);
    }
  }

  ~ObjectPool() {}
};

int main() {
  ObjectPool<Foo> op;
  auto f = op.acquire();
  cout << f->a << endl;

  // get object from pool
  // return object to pool
  //
  //
}
