#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h> // to print to std::cerr
#include <iostream>
#include <new>
#include <string>
using namespace std;
using fmt::print;
using std::cerr;
// TODO: operator[], delete, destructor
// operator [][]?
// operator[] will be tricky - might need StringProxy object and/or a custom
// String class because operator= in there will need to be custom
// make sure reserve reserves for both arrays - 2 diff reserves?

class PackedStringArray {
private:
  class StringProxy {

    void operator=(string s) {}
  };

public:
  void print_all() {

    print("*****PackedStringArray*****\n");
    print(cerr, "m_size: {}\n", m_size);
    print(cerr, "m_next_index: {}\n", m_next_index);
    print(cerr, "m_next_offset: {}\n", m_next_offset);
    print(cerr, "m_bytes_used: {}\n", m_bytes_used);
    print(cerr, "m_expected_string_length: {}\n", m_expected_string_length);
    print_indices();
    print_strings();
  }
  void print_indices() {
    print(cerr, "Indices: ");
    for (size_t i = 0; i < m_size; ++i) {
      print(cerr, "({}, {})", i, m_indices[i]);
    }
    print(cerr, "\n");
  }
  void print_strings() {
    print(cerr, "Strings: ");
    for (size_t i = 0; i < m_bytes_used; ++i) {
      print(std::cerr, "{}", m_strings[i]);
    }
    print(cerr, "\n");
  }

  size_t size() { return m_size; }
  size_t capacity() { return m_bytes_used + m_bytes_free; }
  size_t bytes_used() { return m_bytes_used; }
  size_t bytes_free() { return m_bytes_free; }

  char *data() { return m_strings; }
  size_t *indices() { return m_indices; }

  // private:
  // INVARIANT:
  // m_data[i] == m_data + m_indices[i];
  // - so we can easily lookup m_data[i]
  size_t *m_indices = 0;
  char *m_strings = nullptr;

  size_t m_next_index = 0;
  size_t m_next_offset = 0;

  size_t m_reserve_factor = 2;
  size_t m_expected_string_length = 10;

  size_t m_size = 0; // number of indices in the two arrays
  // size_t m_next_index = 0; // where to put the next string
  size_t m_bytes_used = 0; // used bytes in m_strings
  size_t m_bytes_free = 0; // free bytes in m_strings

  void reserve();

  PackedStringArray(size_t bytes = 0) {

    if (bytes == 0) {
      return;
    }
    reserve(bytes);

    // print(cerr, "CTOR\n");
    // print_all();
  }
  void reserve(size_t bytes) {
    if (bytes <= m_bytes_used + m_bytes_free)
      return;
    if (m_size > 0)
      m_expected_string_length = sizeof(m_strings) / (m_size - 1);

    auto new_strings = new char[bytes];
    m_bytes_free = bytes - m_bytes_used;

    // copy all of m_strings into new_strings
    for (size_t i = 0; i < m_bytes_used; ++i) {
      new_strings[i] = m_strings[i];
    }

    auto new_indices = new size_t[100]; // temp - Needs fix
    for (size_t i = 0; i < m_size; ++i) {
      new_indices[i] = m_indices[i];
    }

    // print("RESERVE\n");
    // print_all();

    delete[] m_strings;
    delete[] m_indices;
    m_strings = new_strings;
    m_indices = new_indices;
  }

  void push_back(std::string str) {
    // INVARIANT:
    // m_data[i] = m_data + m_indices[i];
    size_t ssize = str.size();

    // size_t m_next_index = 0;
    // size_t m_next_offset = 0;

    if (ssize > m_bytes_free)
      reserve(m_size * m_expected_string_length * m_reserve_factor);

    if (m_size == 0) {
      m_indices[0] = 0;

    } else {
      m_indices[m_size] = m_indices[m_size - 1] + ssize;
    }

    for (size_t i = 0; i < ssize; ++i)
      m_strings[m_next_offset + i] = str[i];

    ++m_size;
    m_next_index += 1;
    m_next_offset += ssize;
    m_bytes_used += ssize;
    m_bytes_free -= ssize;
    // print("Push Back: {}\n", str);
    // print_all();
  }
  std::string to_str() {
    std::string output(m_strings, m_bytes_used);
    return output;
  }
}
}
;
