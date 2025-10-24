#include <algorithm>
#include <cassert>
#include <cctype>
#include <complex>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main() {
  std::string str1{"Quick  Red  Dog"};
  std::cout << "1) " << std::quoted(str1) << '\n';
  const auto noSpaceEnd = std::remove(str1.begin(), str1.end(), ' ');
  std::cout << "2) " << std::quoted(str1) << '\n';

  std::cout << "2) " << std::quoted(noSpaceEnd) << '\n';

  // The spaces are removed from the string only logically.
  // Note, we use view, the original string is still not shrunk:
  std::cout << "3) " << std::quoted(std::string_view(str1.begin(), noSpaceEnd))
            << ", size: " << str1.size() << '\n';

  str1.erase(noSpaceEnd, str1.end());
  // The spaces are removed from the string physically.
  std::cout << "4) " << std::quoted(str1) << ", size: " << str1.size() << '\n';

  std::string str2 = "Jumped\n Over\tA\vLazy \t  Fox\r\n";
  str2.erase(std::remove_if(str2.begin(), str2.end(),
                            [](unsigned char x) { return std::isspace(x); }),
             str2.end());
  std::cout << "5) " << std::quoted(str2) << '\n';

  std::vector<std::complex<double>> nums{{2, 2}, {1, 3}, {4, 8}};
#ifdef __cpp_lib_algorithm_default_value_type
  nums.erase(std::remove(nums.begin(), nums.end(), {1, 3}), nums.end());
#else
  nums.erase(std::remove(nums.begin(), nums.end(), std::complex<double>{1, 3}),
             nums.end());
#endif
  assert((nums == std::vector<std::complex<double>>{{2, 2}, {4, 8}}));
}
