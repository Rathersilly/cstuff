#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <std::bidirectional_iterator It,
          Compare<typename It::value_type, typename It::value_type> Fun>
void foo(It first, It last, Fun &fun) {

  cout << fun(*first, *(--last)) << endl;
}
int main(int argc, char *argv[]) {
  auto fun = [](int a, int b) { return a < b; };
  std::vector<int> vec{1, 2};
  foo(vec.begin(), vec.end(), fun);
  return 0;
}
