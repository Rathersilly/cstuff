#include <iomanip>
#include <iostream>
#include <random>
#include <string_view>
#include <vector>
using std::cout, std::endl, std::setw;

// Compile-time type name extractor
template <typename T> constexpr std::string_view type_name() {
#if defined(__clang__)
  std::string_view name = __PRETTY_FUNCTION__;
  cout << "CCCCC" << name << endl;
  auto start = name.find("T = ") + 4;
  auto end = name.find_first_of(';', start);
  return name.substr(start, end - start);
#elif defined(__GNUC__)
  std::string_view name = __PRETTY_FUNCTION__;
  cout << "GGGGG" << name << endl;
  auto start = name.find("with T = ") + 8;
  auto end = name.find_first_of(';', start);
  return name.substr(start, end - start);
#else
  return "unsupported compiler";
#endif
}

template <typename N, typename T, typename U> void printRandoms(N n, T t, U u) {
  std::cout << n << " random numbers from " << type_name<T>() << " using "
            << type_name<U>() << "\n";
}

int main() {
  int x = 42;
  double y = 3.14;
  std::mt19937 gen{std::random_device{}()};

  cout << type_name<decltype(gen)>() << endl;
  // std::cout << "Type of x: " << type_name<decltype(x)>() << "\n";
  // std::cout << "Type of y: " << type_name<decltype(y)>() << "\n";
  // std::cout << "Type of gen: " << type_name<decltype(gen)>() << "\n\n";

  // printRandoms(5, y, gen);
}
