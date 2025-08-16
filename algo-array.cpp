#include "my_helpers.h"
#include <algorithm> // std::shuffle, sort
#include <array>
#include <color_macros.h>
#include <functional>
#include <iostream>
#include <memory>
#include <typeinfo>
using namespace std;
using namespace my;

template <typename T, int N> void move_zeros_to_end(array<T, N> &arr) {
  auto last_nonzero_index = arr.size() - 1;
  for (int i = 0; i < arr.size(); ++i) {
    while (arr[last_nonzero_index] == 0) {
      last_nonzero_index -= 1;
      if (last_nonzero_index <= i)
        return;
    }
    if (arr[i] == 0) {
      swap(arr[i], arr[last_nonzero_index]);
      last_nonzero_index -= 1;
    }
    if (last_nonzero_index <= i)
      return;
  }
}
int main(int argc, char *argv[]) {
  // auto arr = create_random_array<int, 20>();
  auto arr = create_random_array<int, 20>(0, 3);
  // array<int, 5> arr{0, 1, 0, 2, 3};
  // array<int, 10> arr{0, 1, 0, 2, 3, 4, 2, 8, 0, 0};
  print(arr);
  move_zeros_to_end<int, 20>(arr);
  print(arr);
  cout << mt << endl;
  cout << mt() << endl;
  cout << mt() << endl;
  cout << mt() << endl;
  cout << mt() << endl;

  cout << sizeof(mt()) << endl;
  cout << typeid(mt()).name() << endl;
  unsigned int z = 0;
  --z;
  cout << z << endl;
  cout << sizeof(z) << endl;
  cout << typeid(z).name() << endl;

  return 0;
}

