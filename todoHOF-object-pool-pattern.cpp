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

public:
  vector<T> elem;
  int max_elements;
  vector<int> indexes_in_use;
  vector<int> free_indexes;
  std::unique_ptr<T, std::function<void(T *)>> acquire() {
    if (free_indexes.empty()) {
      std::cerr << "no free indexes" << std::endl;
      throw std::runtime_error("pool exhausted");
    }
    int index = free_indexes.back();
    free_indexes.pop_back();
    indexes_in_use.push_back(index);

    auto deleter = [this, index](T *ptr) mutable {
      this->free_indexes.push_back(index);

      auto stored_index = std::find(this->indexes_in_use.begin(),
                                    this->indexes_in_use.end(), index);
      if (stored_index != this->indexes_in_use.end()) {
        this->indexes_in_use.erase(stored_index);
      }
    };

    auto d = elem[index];
    return std::unique_ptr<T, std::function<void(T *)>>(elem.data() + index,
                                                        deleter);
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
  cout << "free_indexes: ";
  print_vector(op.free_indexes);

  cout << "indexes_in_use: ";
  print_vector(op.indexes_in_use);
  {
    auto f = op.acquire();
    cout << f->a << endl;
    cout << "free_indexes: ";
    print_vector(op.free_indexes);

    cout << "indexes_in_use: ";
    print_vector(op.indexes_in_use);
  }
  cout << "free_indexes: ";
  print_vector(op.free_indexes);

  cout << "indexes_in_use: ";
  print_vector(op.indexes_in_use);
  // get object from pool
  // return object to pool
  //
  //
}
