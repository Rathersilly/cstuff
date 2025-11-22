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
#include <color_macros.h>
#include <iostream>
#include <list>
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
class MyUnorderedSet {

public:
  MyUnorderedSet(size_t buckets = 5) : m_size{0}, m_bucket_count{buckets} {
    m_table.resize(buckets);
  }

  void insert(Key item) {
    size_t index = m_hasher(item) % m_bucket_count;
    for (const auto &table_item : m_table[index]) {
      if (m_key_equal(table_item, item))
        return;
    }
    m_table[index].push_back(item);
    ++m_size;
  }
  void remove(Key item) {
    size_t index = m_hasher(item) % m_bucket_count;
    for (auto it = m_table[index].begin(); it != m_table[index].end(); ++it) {
      if (m_key_equal(*it, item)) {
        m_table[index].erase(it);
        --m_size;
        return;
      }
    }
  }
  size_t count(Key item) { // 0 or 1 for unordered set
    size_t index = m_hasher(item) % m_bucket_count;
    size_t memo = 0;
    for (const auto &thing : m_table[index]) {
      if (m_key_equal(thing, item))
        ++memo;
    }
    return memo;
  }
  bool contains(Key item) {
    size_t index = m_hasher(item) % m_bucket_count;
    for (const auto &m_tableitem : m_table[index]) {
      if (m_key_equal(m_tableitem, item))
        return true;
    }
    return false;
  }
  size_t size() { return m_size; }
  size_t bucket_count() { return m_bucket_count; }
  size_t bucket(Key item) {
    size_t index = m_hasher(item) % m_bucket_count;
    return (index);
  }

  void rehash(size_t new_buckets) {
    // if (m_size)
  }

  float load_factor() {
    if (m_size == 0)
      return 0.0;
    return static_cast<float>(m_size) / static_cast<float>(m_bucket_count);
  }
  float max_load_factor() const { return m_max_load_factor; }
  void max_load_factor(float new_max) { m_max_load_factor = new_max; }

private:
  Hash m_hasher;
  KeyEqual m_key_equal;
  vector<list<Key>> m_table;
  size_t m_size = 0;
  size_t m_bucket_count = 0;
  float m_max_load_factor = 1;
};
