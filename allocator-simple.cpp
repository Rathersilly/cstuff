#include <color_macros.h>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class IntAllocator {
  using value_type = int;
  int count = 0;

public:
  int *allocate(int space) {
    TRACE_GREEN();
    ++count;
    cout << "allocated " << count << " times!" << endl;
    int *temp = new int[space];
    return temp;
  }
  void deallocate(int *ptr) { delete[] ptr; }
};

class Vector {

public:
  int mSize;
  int mCapacity;
  int mReserveFactor = 2;
  int *mData = nullptr;
  IntAllocator mAllocator{};

public:
  Vector(int size = 0) : mSize{size}, mCapacity{size} {
    if (mCapacity > 0) {
      reserve_allocate(mCapacity);
    }
  }

  void reserve(int space) {
    if (space <= mCapacity) {
      return;
    } else {
      int *temp = new int[space];
      for (int i = 0; i < mSize; ++i) {
        temp[i] = mData[i];
      }
      if (mData)
        delete[] mData;
      mCapacity = space;
    }
  }
  void reserve_allocate(int space) {
    TRACE_GREEN();

    if (space <= mCapacity) {
      return;
    } else {
      int *temp = mAllocator.allocate(space);
      for (int i = 0; i < mSize; ++i) {
        temp[i] = mData[i];
      }
      delete[] mData;
      mData = temp;
      mCapacity = space;
    }
  }
  void push_back(int x) {
    if (mSize < mCapacity) {
      mData[mSize] = x;
    } else {
      reserve_allocate(mCapacity * mReserveFactor);
      mData[mSize] = x;
    }
    ++mSize;
  }
  int &operator[](int index) { return mData[index]; }
};

int main(int argc, char *argv[]) {
  IntAllocator alloc;
  Vector v;
  v.reserve_allocate(10);
  cout << v.mSize << " " << v.mCapacity << endl;
  v.reserve_allocate(11);
  cout << v.mSize << " " << v.mCapacity << endl;
  v.reserve_allocate(11);
  cout << v.mSize << " " << v.mCapacity << endl;
  v.reserve_allocate(12);
  cout << v.mSize << " " << v.mCapacity << endl;
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  for (int i = 0; i < 10; ++i) {
    cout << v[i] << " ";
  }
  cout << endl;

  vector<int> vv;
  cout << "fadf" << endl;
  cout << vv.size() << endl;
  cout << "cap: " << vv.capacity() << endl;
  vv.push_back(3);
  cout << vv.size() << endl;
  cout << "cap: " << vv.capacity() << endl;
  vv.push_back(3);
  cout << vv.size() << endl;
  cout << "cap: " << vv.capacity() << endl;
  vv.push_back(3);
  cout << vv.size() << endl;
  cout << "cap: " << vv.capacity() << endl;
  vv.push_back(3);
  cout << vv.size() << endl;
  cout << "cap: " << vv.capacity() << endl;
  vv.push_back(3);
  cout << vv.size() << endl;
  cout << "cap: " << vv.capacity() << endl;
  // cout << vv.at(0) << endl;
  return 0;
}
