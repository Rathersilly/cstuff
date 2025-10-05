// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2 // -libs IN THAT ORDER
// remember to link in order from most dependent -> least dependent

#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
//
// unsigned int Factorial(unsigned int number) {
//   return number <= 1 ? number : Factorial(number - 1) * number;
// }
//
// TEST_CASE("Factorials are computed", "[factorial]") {
//   REQUIRE(Factorial(1) == 1);
//   REQUIRE(Factorial(2) == 2);
//   REQUIRE(Factorial(3) == 6);
//   REQUIRE(Factorial(10) == 3628800);
// }
#include "insertion_sort.h"
#include <algorithm>
#include <color_macros.h>
#include <random>
#include <vector>
using namespace std;

TEST_CASE("insertion_sort", "[insertion_sort]") {
  vector<int> vec(20);
  cout << "hi";
  // std::generate(vec.begin(), vec.end(), [] { return mt() % 10; });
  // for (int i = 0; i < 20; ++i) {
  //   std::generate(vec.begin(), vec.end(), [] { return mt() % 10; });
  //   cout << "before: ";
  //   // print_vector(vec);
  //   // insertion_sort(vec.begin(), vec.end());
  //   // cout << "sorted: ";
  //   // print_vector(vec);
  //   cout << "-----" << endl;
  // }
  // insertion_sort(vec);
  // REQUIRE(is_sorted(vec.begin(), vec.end()) == true);
  int i = 2;
  REQUIRE(i == true);
}
