#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> void print_vector(const vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  cout << endl;
}
bool equals8(int x) {
  /* x == 8 ? true : false; */
  if (x == 8)
    return true;
  return false;
}
int main(int argc, char *argv[]) {
  vector<int> v;
  for (int i = 4; i >= 0; --i) {
    v.push_back(i * 2);
  }

  // find
  auto item = std::find(v.begin(), v.end(), 4);
  print_vector(v);
  cout << *item << endl; // 4
  cout << (item - v.begin()) << endl;
  // find if
  cout << "find_if()" << endl;
  item = std::find_if(v.begin(), v.end(), equals8);
  cout << *item << endl;

  // sort
  sort(v.begin(), v.end());
  print_vector(v);

  return 0;
}
