// unordered_set set uses a hash map (vector<List<Key>>) to store values
// - The vector holds buckets, index = hash(value) % num_buckets
// - Each bucket contains all values with that hash
//
// Insertion, deletion, lookup are amortized O(1)
// - worst case O(n) with many collisions (poor hash fn, unlucky distribution)
//
// amortized = over time assuming proper management
// - eg rehashing(increasing # of buckets to shrink avg bucket size)

// this implementation uses hash chaining upon collision
// - collisions are added to linked list
#include <algorithm>
#include <color_macros.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>
// TODO: rehash, load_factor, etc

using namespace std;

template <class T> void print_vector(const vector<T> &v) {
  for (auto &a : v)
    cout << a << " ";
  cout << endl;
}

template <class Key, class Hash = std::hash<Key>,
          class KeyEqual = std::equal_to<Key>>
class myUnorderedSet {
  // private:
public:
  Hash hasher_;
  KeyEqual key_equal_;
  vector<list<Key>> table_;
  size_t bucket_count_;
  size_t size_ = 0;
  float max_load_factor_ = 1;

public:
  myUnorderedSet(size_t buckets = 5) : size_{0}, bucket_count_{buckets} {
    table_.resize(buckets);
  }

  void insert(Key item) {
    size_t index = hasher_(item) % bucket_count_;
    for (const auto &table_item : table_[index]) {
      if (key_equal_(table_item, item))
        return;
    }
    table_[index].push_back(item);
    ++size_;
  }
  void remove(Key item) {
    size_t index = hasher_(item) % bucket_count_;
    for (auto it = table_[index].begin(); it != table_[index].end(); ++it) {
      if (key_equal_(*it, item)) {
        table_[index].erase(it);
        --size_;
        return;
      }
    }
  }
  size_t count(Key item) { // 0 or 1 for unordered set
    size_t index = hasher_(item) % bucket_count_;
    size_t memo = 0;
    for (const auto &thing : table_[index]) {
      if (key_equal_(thing, item))
        ++memo;
    }
    return memo;
  }
  bool contains(Key item) {
    size_t index = hasher_(item) % bucket_count_;
    for (const auto &table_item : table_[index]) {
      if (key_equal_(table_item, item))
        return true;
    }
    return false;
  }
  size_t size() { return size_; }
  size_t bucket_count() { return bucket_count_; }
  size_t bucket(Key item) {
    size_t index = hasher_(item) % bucket_count_;
    return (index);
  }

  void rehash(int new_buckets) {
    // if (size_)
  }

  float load_factor() {
    if (bucket_count_ == 0)
      return 0.0;
    return static_cast<float>(size_) / static_cast<float>(bucket_count_);
  }
  float max_load_factor() const { return max_load_factor_; }
  void max_load_factor(float new_max) { max_load_factor_ = new_max; }
};
