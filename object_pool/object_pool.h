#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_set>
using namespace std;
// TODO: find out how to use this as/with custom allocator
// poolable? should that be an aggregate to another class?
//

struct Object {
  Object *next_free = nullptr;
  string name = "none";
  int id = 0;
  bool in_use = false;

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

template <class T>
concept Poolable = requires(T obj) {
  { obj.next_free } -> std::convertible_to<T *>;
  { obj.in_use } -> std::convertible_to<bool>;
};

// Possible todo: implement optional strict behavior
// to throw when failing acquire/release, etc
// template <Poolable T, bool Strict = false>
template <Poolable T> struct ObjectPool {
public:
  ObjectPool(size_t capacity, bool initialize_ = false)
      : capacity_{capacity}, num_used_{0} {
    // this can be delegated to MemoryArena class
    size_t bytes = capacity * sizeof(T);
    size_t alignment = alignof(T);
    // aligned_alloc requires bytes to be multiple of alignment
    if (bytes % alignment != 0)
      bytes += alignment - (bytes % alignment);

    data_ =
        static_cast<T *>(::operator new[](bytes, std::align_val_t{alignment}));
    // more C-like:
    // data_ = static_cast<T *>(aligned_alloc(alignment, bytes));

    if (initialize_)
      initialize();
    else
      free_objects_ = nullptr;
  }
  ~ObjectPool() {

    if constexpr (!std::is_trivially_destructible_v<T>) {
      for (size_t i = 0; i < num_allocated_; ++i)
        std::destroy_at(&data_[i]);
    }

    ::operator delete[](data_, std::align_val_t{alignof(T)});
    // std::free(data_); // C-style
  }

  // fill our empty memory with blank objects,
  // linked together with "free list" to O(1) find an usable object
  void initialize(std::optional<size_t> init_size = nullopt) {
    size_t free_slots = capacity_ - num_allocated_;
    if (free_slots == 0)
      return;

    size_t slots_to_init = init_size.value_or(free_slots);

    for (auto i = num_allocated_; i < (num_allocated_ + slots_to_init - 1);
         ++i) {
      T *temp = new (&data_[i]) T();
      temp->id = i;
      temp->next_free = &data_[i + 1];
    }

    // handle last element separately
    T *last = new (&data_[num_allocated_ + slots_to_init - 1]) T();
    last->id = num_allocated_ + slots_to_init - 1;
    last->next_free = nullptr;

    if (free_objects_) {
      last->next_free = free_objects_;
    }
    free_objects_ = &data_[num_allocated_];
    num_allocated_ += slots_to_init;
  }
  void expand(size_t count) { initialize(count); }

  template <class... Args> [[nodiscard]] T *acquire(Args &&...args) {
    if (num_used_ == capacity_)
      return nullptr;
    if (!free_objects_) // above if () should catch this
      return nullptr;

    T *obj;
    if (free_objects_) { // object exists already
      obj = free_objects_;

    } else { // allocate object into free space
      obj = new (free_objects_) T(std::forward<Args>(args)...);
      num_allocated_ += 1;
    }
    obj->reset(std::forward<Args>(args)...);
    obj->next_free = free_objects_->next_free;
    free_objects_ = obj->next_free;
    ++num_used_;
    return obj;
  }

  void release(T *obj) {
    // detect double release in debug mode
    assert(obj && obj->in_use);

    if (!obj || obj->in_use == false) // defensive, not strict
      return;

    obj->in_use = false;
    obj->next_free = free_objects_;
    free_objects_ = obj;
    --num_used_;
  }

  void release_all() {
    for (size_t i = 0; i < num_allocated_; ++i) {
      if (data_[i].in_use == true)
        release(&data_[i]);
    }
  }

  size_t num_used() const { return num_used_; }
  size_t capacity() const { return capacity_; }
  size_t num_free() const { return num_allocated_ - num_used_; }
  size_t num_allocated() const { return num_allocated_; }
  bool is_empty() const { return num_used_ == 0; }
  bool is_full() const { return capacity_ - num_used_ == 0; }
  T *data() { return data_; }
  T *first() { return (num_used_ > 0) ? &data_[0] : nullptr; }
  template <Poolable U>
  friend bool check_freelist_integrity(const ObjectPool<U> &pool);

private:
  T *data_ = nullptr;
  T *free_objects_ =
      nullptr;               // linked list of free objects for O(1) acquisition
  size_t capacity_ = 0;      // maximum num_allocated
  size_t num_allocated_ = 0; // objects created
  size_t num_used_ = 0;      // objects in use
};

// Simple function to verify integrity of a linked list
template <Poolable T> bool check_freelist_integrity(const ObjectPool<T> &pool) {

  size_t count = 0;
  const T *node = pool.free_objects_;
  std::unordered_set<const T *> visited;

  while (node) {
    if (visited.contains(node)) {
      throw logic_error("Cycle detected in free list");
      return false;
    }
    visited.insert(node);

    if (node < pool.data_ || node >= pool.data_ + pool.capacity_) {
      throw logic_error("Node out of range");
      return false;
    }

    node = node->next_free;
    ++count;
  }

  if (count != pool.num_allocated_ - pool.num_used_) {
    throw logic_error("Free list count mismatch");
    return false;
  }

  return true;
}
