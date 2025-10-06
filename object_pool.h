#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
using namespace std;

struct Object {
  string name = "none";
  int id;
  bool in_use = false;
  Object *next_free;

  Object() {}
  Object(Object *next) : next_free{next} {}
  Object(Object *next, string name) : next_free{next}, name{name} {}
  Object(string n, int i) : name{n}, id{i} {}

  void reset() { in_use = true; }
  void reset(string n, int i) {
    name = n;
    id = i;
    in_use = true;
  }
  void display() { cout << name << " " << id << endl; }

  bool operator<(const Object &s) const { return id < s.id; }
};

template <class T> struct ObjectPool {
public:
  ObjectPool(size_t capacity, bool initialize_ = false)
      : capacity_{capacity}, num_used_{0} {
    // this will be delegated to MemoryArena class
    data_ = static_cast<T *>(malloc(capacity_ * sizeof(T)));
    if (initialize_)
      initialize();
    else
      free_objects = nullptr;
  }
  ~ObjectPool() { std::free(data_); }

  template <class... Args> T *acquire(Args &&...args) {
    if (num_used_ == capacity_)
      return nullptr;

    T *obj;
    if (free_objects) { // object exists already
      obj = free_objects;

    } else { // allocate object into free space
      obj = new (free_objects) T(std::forward<Args>(args)...);
      num_allocated_ += 1;
    }
    obj->reset(std::forward<Args>(args)...);
    obj->next_free = free_objects->next_free;
    free_objects = obj->next_free;
    ++num_used_;
    return obj;
  }

  void release(T *obj) {
    if (!obj || obj->in_use == false)
      return;
    obj->in_use = false;
    obj->next_free = free_objects;
    free_objects = obj;
    --num_used_;
  }

  void release_all() {
    for (int i = 0; i < num_allocated_; ++i) {
      if (data_[i].in_use == true)
        release(&data_[i]);
    }
  }

public:
  // private:
  T *data_;
  T *free_objects;           // linked list of free objects for O(1) acquisition
  size_t capacity_ = 0;      // maximum num_allocated
  size_t num_allocated_ = 0; // objects created
  size_t num_used_ = 0;      // objects in use

  // fill our empty memory with blank objects,
  // linked together with "free list" to O(1) find an usable object
  void initialize(std::optional<size_t> init_size = nullopt) {
    size_t free_slots = capacity_ - num_allocated_;
    if (free_slots == 0)
      return;

    size_t slots_to_init = init_size.value_or(free_slots);

    for (int i = num_allocated_; i < (num_allocated_ + slots_to_init - 1);
         ++i) {
      T *temp = new (&data_[i]) T();
      temp->id = i;
      temp->next_free = &data_[i + 1];
    }

    // handle last element separately
    T *last = new (&data_[num_allocated_ + slots_to_init - 1]) T();
    last->id = num_allocated_ + slots_to_init - 1;
    last->next_free = nullptr;

    num_allocated_ += slots_to_init;
    free_objects = &data_[0]; // NOPE what if its in use
  }
  size_t num_used() const { return num_used_; }
  size_t capacity() const { return capacity_; }
  size_t num_free() const { return num_allocated_ - num_used_; }
  bool is_empty() const { return num_used_ == 0; }
  bool is_full() const { return capacity_ - num_used_ == 0; }
  T *data() { return data_; }
  T *first() { return (num_used_ > 0) ? &data_[0] : nullptr; }
};
