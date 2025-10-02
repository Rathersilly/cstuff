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
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

template <class T> void print_vector(const vector<T> &v) {
  for (auto &a : v)
    cout << a << " ";
  cout << endl;
}

template <class Key, class Hash = std::hash<Key>,
          class KeyEqual = std::equal_to<Key>>
class myUnorderedSet {
  Hash hasher_;
  KeyEqual key_equal_;
  vector<list<Key>> table_;
  size_t bucket_count_;
  size_t size_;

public:
  myUnorderedSet(size_t buckets = 50) : bucket_count_{buckets} {
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
        return;
      }
    }
    --size_;
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
  size_t size() { return size; }
};

int main(int argc, char *argv[]) {
  myUnorderedSet<int> set;
  myUnorderedSet<string> sset;
  for (int i = 0; i < 10; ++i)
    set.insert(i);
  sset.insert("hello");
  sset.insert("hi");
  sset.insert("whatsup");
  sset.insert("whatssup");
  sset.insert("whattsup");
  sset.insert("whatqsup");
  sset.insert("whatfsadsup");
  int num = 3;
  set.insert(num);
  cout << boolalpha << "Set contains " << num << ": " << set.contains(num)
       << endl;
  set.remove(3);
  cout << boolalpha << "Set contains " << num << ": " << set.contains(num)
       << endl;
  set.remove(3);
  set.insert(num);
  cout << boolalpha << "Set contains " << num << ": " << set.contains(num)
       << endl;
  set.remove(7);
  set.remove(6);
  for (int i = 0; i < 15; ++i) {

    cout << boolalpha << "Set contains " << i << ": " << set.contains(i)
         << endl;
  }

  cout << set.count(6) << set.count(5);
  return 0;
}
