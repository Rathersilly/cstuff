#include "include/test.h"
#include "insertion_sort.h"
#include "search.h"
#include <algorithm>
#include <functional>
#include <random>
#include <vector>
using namespace std;
std::mt19937 mt{std::random_device{}()};

vector<int> get_random_vector(
    size_t n, std::function<unsigned int()> fun = [] { return mt(); }) {

  vector<int> vec(n);
  std::generate(vec.begin(), vec.end(), [=] { return fun() % 10; });

  return vec;
}

int main() {
  vector<int> vec{1, 2, 3, 4, 5};

  test_results();
  return 0;
}
