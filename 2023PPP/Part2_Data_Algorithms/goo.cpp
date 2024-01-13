#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>
#include <string_view>
#include <vector>
using namespace std;

void copy(int *a, int *b, int *c) {
  while (a != b) {
    *c = *a;
    ++a;
    ++c;
  }
}
template <typename T, typename A = allocator<T>>
void print_vector(const vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  cout << endl;
}
using namespace std;
int main(int argc, char *argv[]) {

  std::mt19937 mt{std::time(nullptr)};
  vector<int> v{5, 2, 3, 4, 1};
  sort(v.begin(), v.end());
  print_vector<int>(v);
  vector<int> rands{};

  for (int i = 0; i < 10; ++i) {
    rands.push_back(mt());
  }
  print_vector<int>(rands);
}
