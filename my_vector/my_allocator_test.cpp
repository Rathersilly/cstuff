// No Assertions in here yet - mainly using this with valgrind
#include "my_allocator.h"
#include "my_vector.h"
#include <cstdio>
#include <string>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace fmt;

struct SomeObject {
  // ignoring 035 for brevity - dont make copies!
  int size;
  std::vector<int *> nums;
  std::string *str_ptr;
  SomeObject(int n = 0) : size{n} {
    for (int i = 0; i < size; ++i) {
      nums.push_back(new int(i * i));
    }
    str_ptr = new std::string("hi");
  }
  ~SomeObject() {
    for (int *p : nums) {
      delete p;
    }
    delete str_ptr;
  }
};

TEST_CASE("Custom Allocator with myVector<int>") {
  myVector<int, MyAllocator<int>> arr;
  arr.push_back(0);
  int num = 10;
  for (int i = 0; i < num; ++i)
    arr.push_back(i * 3);

  print("{}\n", arr);
}

TEST_CASE("Custom Allocator<SomeObject> correctly destroys") {
  myVector<SomeObject *, MyAllocator<SomeObject *>> arr;
  // std::vector<SomeObject *> arr;
  SomeObject obj1(3);
  arr.push_back(&obj1);
  SomeObject obj2(5);
  arr.push_back(&obj2);
  SomeObject obj3(7);
  arr.push_back(&obj3);
  print("{}\n", *(obj1.str_ptr));
  for (int i = 0; i < 7; ++i) {
    print("{} ", *(obj3.nums[i]));
  }
  print("\n");
}
