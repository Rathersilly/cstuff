#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Object {
  string name_ = "***uninitialized***";
  int id_;
  bool in_use_ = false;

  Object *next_unused_;
  Object() {}
  Object(Object *next_unused) : next_unused_{next_unused} {}
  Object(Object *next_unused, string name)
      : next_unused_{next_unused}, name_{name} {}
  Object(string name, int id) : name_{name}, id_{id} {}

  void create(string name, int id) {
    name_ = name;
    id_ = id;
    in_use_ = true;
  }

  bool operator<(const Object &s) const { return id_ < s.id_; }
};

template <class T> struct ObjectPool {
public:
  ObjectPool(int size, bool initialize_ = false) : size_{size} {
    data_ = static_cast<T *>(malloc(size_ * sizeof(T)));
    if (initialize_)
      initialize();
    else
      first_unused_ = nullptr;
  }
  ~ObjectPool() { std::free(data_); }

  template <class... Args> T *create(Args &&...args) {

    if (first_unused_) {
      auto next_unused_ = first_unused_.next_unused_;
    }
  }

  string check_name(int offset) { return (data_[offset].name_); }
  // create function for if we dont create them all initially
  //   template <typename... Args>
  // T* create(Args&&... args) {
  //     if (used_ >= size_) {
  //         throw std::bad_alloc(); // pool full
  //     }
  //     // placement new constructs in pre-allocated memory
  //     T* obj = new (&raw[used_]) T(std::forward<Args>(args)...);
  //     ++used_;
  //     return obj;
  // }

// ways of allowing test framework access:
// remember to compile with -DUNIT_TEST
#if !defined(UNIT_TEST)
public:
#else
private:
#endif
  int max_size_;
  int size_;
  T *data_;
  T *first_unused_;

  // fill our empty memory with blank objects,
  // linked together with "free list" to O(1) find an usable object
  // TODO: need many validations here
  // void initialize() {
  //
  //   for (int i = 0; i < size_ - 1; ++i) {
  //     T *temp = new (&data_[i]) T();
  //     temp->next_unused_ = &data_[i + 1];
  //     temp->id_ = i;
  //   }
  //   T *last = new (&data_[size_ - 1]) T();
  //   last->next_unused_ = nullptr;
  //   last->id_ = size_ - 1;
  //
  //   first_unused_ = &data_[0];
  // }
  // initialize should work if data has 0 objects or max_size -1 objects
  void initialize() {
    for (int i = 0; i < size_ - 1; ++i) {
      T *temp = new (&data_[i]) T();
      temp->id_ = i;
      temp->next_unused_ = &data_[i + 1]; // always valid inside loop
    }

    // handle last element separately
    T *last = new (&data_[size_ - 1]) T();
    last->id_ = size_ - 1;
    last->next_unused_ = nullptr;

    first_unused_ = &data_[0];
  }
};
