// ArrayQueue: simply queue using array with front/back indices

#include <iostream>
#include <vector>

using namespace std;

class ArrayQueue {
public:
  ArrayQueue(int s) : m_size{s} { m_array = new int[s]; }

  ~ArrayQueue() { delete[] m_array; }

  void push(int data) {
    if (empty()) {
      m_findex = m_bindex = 0;
      m_array[0] = data;
    } else if (full()) {
      return;
    } else { // queue not full
      ++m_bindex;
      if (m_bindex == m_size)
        m_bindex = 0;
      m_array[m_bindex] = data;
    }
  }

  void pop() {
    if (empty())
      return;

    if (full()) {
      ++m_findex;
      if (m_findex == m_size)
        m_findex = 0;
    }
    // queue size 1
    else if (m_findex == m_bindex) {
      m_findex = m_bindex = -1;
    }
    // queue not full
    else {
      ++m_findex;
      if (m_findex == m_size)
        m_findex = 0;
    }
  }

  int front() { return m_array[m_findex]; }
  int back() { return m_array[m_bindex]; }
  int empty() { return m_findex == -1; }
  int full() {
    if (m_bindex - m_findex == m_size - 1 || m_findex - m_bindex == 1)
      return true;

    return false;
  }

  // return vector of the queue
  vector<int> get_vector() {
    vector<int> vec;
    if (empty())
      return vec;

    auto findex = m_findex;
    auto bindex = m_bindex;

    while (findex != bindex) {
      vec.push_back(m_array[findex]);
      ++findex;
      if (findex == m_size)
        findex = 0;
    }
    vec.push_back(m_array[findex]);
    return vec;
  }

  // return vector of underlying array (for testing purposes)
  vector<int> get_vector_raw() {
    vector<int> vec;
    for (int i = 0; i < m_size; ++i) {
      vec.push_back(m_array[i]);
    }
    return vec;
  }

  // print queue
  void display() {
    auto findex = m_findex;
    auto bindex = m_bindex;

    while (findex != bindex) {
      cout << m_array[findex] << " ";
      ++findex;
      if (findex == m_size)
        findex = 0;
    }

    cout << m_array[findex] << " ";

    cout << endl;
  }

  // print underlying array
  void display_raw() {
    for (int i = 0; i < m_size; ++i)
      cout << m_array[i] << " ";

    cout << endl;
  }

private:
  int m_size;
  int *m_array;
  int m_findex = -1;
  int m_bindex = -1;
};
