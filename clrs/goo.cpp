#define CATCH_CONFIG_MAIN
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cstdint>

uint64_t fibonacci(uint64_t number) {
  return number < 2 ? number : fibonacci(number - 1) + fibonacci(number - 2);
}

TEST_CASE("Benchmark Fibonacci", "[benchmark]") {
  REQUIRE(fibonacci(5) == 5);

  REQUIRE(fibonacci(20) == 6'765);
  BENCHMARK("fibonacci 20") { return fibonacci(20); };

  REQUIRE(fibonacci(25) == 75'025);
  BENCHMARK("fibonacci 25") { return fibonacci(25); };
}

unsigned int Factorial(unsigned int number) {
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
  REQUIRE(Factorial(2) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}
