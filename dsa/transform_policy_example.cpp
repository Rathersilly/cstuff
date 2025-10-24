// g++ -std=c++20 foo.cpp -lCatch2Main -lCatch2

#define CATCH_CONFIG_MAIN
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdint>
#include <execution>
#include <functional>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
using namespace std;

inline void print_vector(const vector<int> vec, string msg = "") {
  cout << msg;
  for (auto &a : vec) {
    cout << a << " ";
  }
  cout << endl;
}
inline void print_vector(const vector<int>::iterator first,
                         const vector<int>::iterator last, string msg = "") {
  cout << msg;
  for (auto a = first; a != last; ++a) {
    cout << *a << " ";
  }
  cout << endl;
}
template <typename ExecPolicy = std::execution::sequenced_policy>
void test_reduce(size_t n, ExecPolicy pol = ExecPolicy{}) {
  vector<int> v(n);
  std::iota(v.begin(), v.end(), 0);
  auto a = std::reduce(pol, v.begin(), v.end(), 0);
  // cerr << a << '\n';
}
uint64_t fibonacci(uint64_t number) {
  return number < 2 ? number : fibonacci(number - 1) + fibonacci(number - 2);
}
template <typename ExecPolicy = std::execution::sequenced_policy>
void test_transform_fib(size_t n, ExecPolicy pol = ExecPolicy{}) {
  vector<int> v(n);
  std::iota(v.begin(), v.end(), 0);
  for_each(pol, v.begin(), v.end(), fibonacci);
  // cerr << a << '\n';
}

template <typename ExecPolicy = std::execution::sequenced_policy>
void test_transform_fib_manual(size_t n, int threads,
                               ExecPolicy pol = ExecPolicy{}) {
  vector<int> v(n);
  vector<thread> vthreads;
  vthreads.reserve(threads);
  std::iota(v.begin(), v.end(), 0);

  auto div = n / threads;

  for (int i = 0; i < threads; ++i) {
    auto begin = v.begin() + i * div;
    auto end = (i == threads - 1) ? v.end() : (begin + div);
    vthreads.push_back(
        std::thread([&, i] { std::for_each(pol, begin, end, fibonacci); }));
  }

  for (auto &t : vthreads)
    t.join();
}

TEST_CASE("Benchmark reduce", "[benchmark]") {
  int n = 30;
  // BENCHMARK("seq reduce") {
  //   return test_reduce(n, execution::seq);
  // };
  // BENCHMARK("par reduce"") {
  //   return test_reduce(n, execution::par);
  // };
  BENCHMARK("seq transfom_fib") {
    return test_transform_fib(n, execution::seq);
  };
  BENCHMARK("par transfom_fib") {
    return test_transform_fib(n, execution::par);
  };
  BENCHMARK("1 thread transfom_fib") {
    return test_transform_fib_manual(n, 1);
  };
  BENCHMARK("2 thread transfom_fib") {
    return test_transform_fib_manual(n, 2);
  };
  BENCHMARK("3 thread transfom_fib") {
    return test_transform_fib_manual(n, 3);
  };
}

// TEST_CASE("Benchmark Fibonacci", "[benchmark]") {
//   REQUIRE(fibonacci(5) == 5);
//
//   REQUIRE(fibonacci(20) == 6'765);
//   BENCHMARK("fibonacci 20") { return fibonacci(20); };
//
//   REQUIRE(fibonacci(25) == 75'025);
//   BENCHMARK("fibonacci 25") { return fibonacci(25); };
// }
//
// unsigned int Factorial(unsigned int number) {
//   return number <= 1 ? number : Factorial(number - 1) * number;
// }
//
// TEST_CASE("Factorials are computed", "[factorial]") {
//   REQUIRE(Factorial(2) == 1);
//
//   REQUIRE(Factorial(2) == 2);
//   REQUIRE(Factorial(3) == 6);
//   REQUIRE(Factorial(10) == 3628800);
// }
