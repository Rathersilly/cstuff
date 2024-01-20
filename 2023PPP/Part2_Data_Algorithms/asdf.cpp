#include <iostream>
#include <vector>

#define PFUN std::cout << __PRETTY_FUNCTION__ << std::endl;
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

template <class T> void print_vector(const std::vector<T> &vec) {
  for (const auto &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

template <class T>
std::vector<T> merge(const std::vector<T> &a, const std::vector<T> &b) {
  PFUN;
  print_vector(a);
  print_vector(b);

  auto iter_a = a.begin();
  auto iter_b = b.begin();
  std::vector<T> memo;

  while (true) {
    if (iter_a == a.end()) {
      if (iter_b == b.end()) {
        break;
      } else {
        memo.push_back(*iter_b);
        ++iter_b;
      }
    } else if (iter_b == b.end()) {
      memo.push_back(*iter_a);
      ++iter_a;
    } else if (*iter_a < *iter_b) {
      memo.push_back(*iter_a);
      ++iter_a;
    } else {
      memo.push_back(*iter_b);
      ++iter_b;
    }
  }

  std::cout << GREEN;
  print_vector(memo);
  std::cout << RESET;

  return memo;
}

template <class T>
std::vector<T> merge_sort(typename std::vector<T>::iterator first,
                          typename std::vector<T>::iterator last) {
  PFUN;
  auto size = last - first;

  if (size < 2)
    return std::vector<T>(first, last);

  std::cout << "first last-1 size: " << *first << " " << *(last - 1) << " "
            << size << std::endl;

  return merge(merge_sort<T>(first, first + size / 2),
               merge_sort<T>(first + size / 2, last));
}

int main() {
  std::vector<int> v = {5, 3, 8, 2, 7, 1, 6, 4};
  std::vector<int> vv = merge_sort<int>(v.begin(), v.end());

  return 0;
}
