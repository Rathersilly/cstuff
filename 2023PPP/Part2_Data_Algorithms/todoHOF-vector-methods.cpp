// HOF TODO
// list and demo the most comming std::vector methods

#include <array>
#include <cstring>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
using namespace std;

int main(int argc, char *argv[]) {
  int i = 0;
  vector<int> a;
  cout << sizeof(vector<int>) << endl;
  cout << a.capacity() << endl;
  a.push_back(2);
  cout << sizeof(vector<int>) << endl;
  cout << a.capacity() << endl;

  return 0;
}
