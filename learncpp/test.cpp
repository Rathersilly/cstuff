// Testing to see if c++17 is enabled
// https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-choosing-a-language-standard/

#include <array>
#include <iostream>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace a::b::c {
inline constexpr std::string_view str{"hello"};
}

template <typename... T>
std::tuple<std::size_t, std::common_type_t<T...>> sum(T... args) {
  return {sizeof...(T), (args + ...)};
}

int main() {
  auto [iNumbers, iSum]{sum(1, 2, 3)};
  std::cout << a::b::c::str << ' ' << iNumbers << ' ' << iSum << '\n';

  std::array arr{1, 2, 3};

  std::cout << std::size(arr) << '\n';

  return 0;
}
