#pragma once
#include <array>
#include <color_macros.h>
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;
// multiple ways to implement deque
// std::deque apparently keeps array of pointers to blocks
// stores first pointer halfway up the array to allow push_front to allocate
// blocks
//
// could also have a doubly linked list of arrays - to have O(1) random access
// you'd need to store # of blocks and do some arithmetic

void print_array(array<int, 8> arr) {
  TRACE();
  for (auto &a : arr) {
    cout << a << " ";
  }
  cout << endl;
}
template <class T, class Allocator = std::allocator<T>> class myDeque {
public:
  myDeque() {
    // T *temp = m_allocator.allocate(m_page_size);
    block_map[b_block] = make_unique<array<T, block_size>>();
    m_size == 0;
  };
  void push_back(T item) {
    // find the correct block
    cout << "push back: " << item << ", size: " << m_size << endl;
    if (b_index < 7) {
      if (m_size == 0) {
        block_map[b_block]->at(0) = item;
      } else {
        b_index += 1;
        block_map[b_block]->at(b_index) = item;
      }
    } else {
      if (block_map[b_block + 1]) {
        cout << "empty back block exists" << endl;
        // (*block_map[b_block])[0] = item; // ugly syntax fixed with unique_ptr
        b_block += 1;
        block_map[b_block]->at(0) = item;
        b_index = 0;
      } else {
        cout << "create new back block" << endl;
        b_block += 1;
        block_map[b_block] = make_unique<array<T, block_size>>();
        block_map[b_block]->at(0) = item;
        b_index = 0;
      }
    }
    ++m_size;
  }
  void push_front(T item) {
    if (f_block < watershed) {
    } else {
      f_block = watershed - 1;
      block_map[f_block] = make_unique<array<T, block_size>>();
      f_index = 7;
      block_map[f_block]->at(f_index) = item;
    }
    ++m_size;
  }

  void pop_back() {
    if (b_index > 0) {
      --b_index;
    } else {
      b_index = 7;
      --b_block;
    }
    --m_size;
  }
  void pop_front() {
    if (f_index < 7) {
      ++f_index;
    } else {
      f_index = 0;
      ++f_block;
    }
    --m_size;
  }

  // Accessors
  T &front() { return (*block_map[f_block])[f_index]; }
  T &back() { return (*block_map[b_block])[b_index]; }

private:
public:
  Allocator m_allocator;
  static constexpr int block_size = 8;
  // std::array<array<T, block_size> *, 64> block_map{nullptr};
  std::array<unique_ptr<array<T, block_size>>, 64> block_map{nullptr};
  int m_size = 0;
  int f_block = 32;
  int b_block = 32;

  int f_index = 0;
  int watershed = 32; // what if they are all push_fronted?
  int b_index = 0;
  void print();
};

template <class T, class Allocator> void myDeque<T, Allocator>::print() {
  TRACE_GREEN();

  if (f_block == b_block) {
    cout << "one block" << endl;
    for (int i = f_index; i < b_index; ++i) {
      cout << i << " ";
    }
    return;
  }
  cout << "f_block:" << endl;
  print_array(*block_map[f_block]);
  for (int i = f_index; i < block_size; ++i) {
    cout << "\nf_block: f_index:" << f_index << " " << i << " "
         << block_map[f_block]->at(i) << endl;
    cout << block_map[f_block]->at(i) << " ";
  }

  cout << "\nblock indices: " << f_block << " " << b_block;
  auto block_index = f_block + 1;
  while (b_block > block_index) {

    cout << "\nwhile:  block index, b_block " << block_index << ", " << b_block
         << endl;
    for (int i = 0; i < block_size; ++i) {
      cout << block_map[block_index]->at(i) << " ";
    }
    ++block_index;
  }
  cout << "\nb_block" << endl;
  for (int i = 0; i < b_index; ++i) {
    cout << block_map[block_index]->at(i) << " ";
  }
}
