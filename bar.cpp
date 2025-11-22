#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class PackedStringArray {

public:
  size_t size() { return m_size; }
  char *data() { return m_strings; }
  char **indices() { return m_indices; }

  // private:
  // index in m_indices is index in m_data
  // data in m_indices is ptr to that index in m_data
  char **m_indices;
  char *m_strings;
  // INVARIANT: m_next_index is the next byte we can write to
  // SO: m_indices[m_next_index] - m_strings == bytes used
  size_t m_next_index;

  size_t m_reserve_factor = 2;
  size_t m_expected_string_length = 10;

  size_t m_size; // number of indices in the two arrays
  size_t m_used_bytes;
  size_t m_free_bytes; // free bytes in m_strings

  void reserve();

  PackedStringArray(size_t size = 0) {
    m_size = size;
    m_next_index = 0;

    if (size == 0) {
      m_free_bytes = 0;
      return;
    }
    reserve(size);
    m_indices = new char *[size];
    m_strings = new char[size * m_expected_string_length];

    m_indices = &m_strings;
    m_free_bytes = sizeof(m_strings);
  }
  void reserve(size_t size) {
    m_expected_string_length = sizeof(m_strings) / (m_next_index - 1);

    auto new_strings =
        new char(sizeof(m_strings) + size * m_expected_string_length);
    // copy all of m_strings into new_strings
    for (size_t i = 0; i < m_size; ++i) {
    }

    // now adjust m_indices

    delete[] m_strings;
  }

  void push_back(std::string s) {
    size_t size = sizeof(s);

    if (size > m_free_bytes)
      reserve();
    if (size < m_free_bytes) {
      auto next_address = m_indices[m_next_index];
      // append next address to index array
      // invariant: m_indices is always large enough for this
      m_indices[m_size] = next_address;
    }
  }
};
