#include <algorithm>
#include <color_macros.h>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
std::mt19937 mt{std::random_device{}()};

void print_vector(const vector<int> vec) {
  for (auto &a : vec) {
    cout << a << " ";
  }
  cout << endl;
}

template <class RandomIt> void insertion_sort(RandomIt first, RandomIt last) {
  // TRACE_GREEN();
  if (first + 1 == last)
    return;
  for (auto i = first + 1; i != last; ++i) { // sorted subarray [first,i - 1)
    auto key = *i;
    auto j = i;
    while (j != first && key < *(j - 1)) {
      *j = *(j - 1);
      --j;
    }
    *j = key;
  }
}

template <class T, class Compare = std::less<T>>
void insertion_sort(vector<T> &vec, Compare cmp = Compare{}) {
  if (vec.size() == 0)
    return;
  // loop invariant: A[0,i-1] = sorted subarray
  for (int i = 1; i < vec.size(); ++i) {
    int key = vec[i]; // key is the item to be inserted into sorted subarray
    int j = i - 1;    // j will iterate backward through sorted subarray
    while (j >= 0 && cmp(key, vec[j])) {
      vec[j + 1] = vec[j]; // key is smaller: shift the tested item up 1
      --j;
    }
    vec[j + 1] = key; // we've found the proper index for key
  }
}

int main(int argc, char *argv[]) {
  // vector<int> vec{3, 6, 7, 5, 3, 5, 6, 2, 9, 1};

  vector<int> vec(20);
  std::generate(vec.begin(), vec.end(), [] { return rand() % 10; });
  print_vector(vec);
  // insertion_sort(vec, std::less<>{});
  insertion_sort(vec);
  print_vector(vec);

  cout << "-----" << endl;
  std::generate(vec.begin(), vec.end(), [] { return mt() % 10; });
  print_vector(vec);
  insertion_sort(vec);
  print_vector(vec);
  insertion_sort(vec.begin(), vec.end());
  print_vector(vec);
  cout << "-----" << endl;
  for (int i = 0; i < 20; ++i) {
    std::generate(vec.begin(), vec.end(), [] { return mt() % 10; });
    cout << "before: ";
    print_vector(vec);
    insertion_sort(vec.begin(), vec.end());
    cout << "sorted: ";
    print_vector(vec);
    cout << "-----" << endl;
  }
  return 0;
}
