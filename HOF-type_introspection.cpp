#include "color_macros.h"
#include <cxxabi.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <string_view>
#include <type_traits>
#include <typeinfo>
using std::cout, std::endl, std::setw;

// Return demanged name with __cxa_demangle()
template <typename T> std::string type_name_demangled() {
  int status = 0;
  std::unique_ptr<char, void (*)(void *)> res{
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
      std::free};
  return (status == 0) ? res.get() : typeid(T).name();
}

// Compile-time type name extractor from __PRETTY_FUNCTION__
template <typename T>
constexpr std::string_view type_name_from_pretty_function() {
#if defined(__clang__) // __PRETTY_FUNCTION__ varies by compiler
  std::string_view name = __PRETTY_FUNCTION__;
  auto start = name.find("T = ") + 4;
  auto end = name.find_first_of(';', start);
  return name.substr(start, end - start);
#elif defined(__GNUC__)
  std::string_view name = __PRETTY_FUNCTION__;
  auto start = name.find("with T = ") + 8;
  auto end = name.find_first_of(';', start);
  return name.substr(start, end - start);
#else
  return "unsupported compiler";
#endif
}

// macro to print a type
#define PRINT_TYPEVAL(x)                                                       \
  std::cout << #x << " = " << (x) << " : "                                     \
            << type_name_demangled<decltype(x)>() << "\n";

int main() {

  // deduce types with decltype and auto
  int i = 0;
  decltype(i) j = 1;
  auto k = 2;
  std::string s = "hello";

  std::mt19937 mt;
  std::uniform_int_distribution<> die6{1, 6};

  cout << "<type_traits> contains tools for type comparison and manipulation"
       << endl;
  // is_integral_v is helper for is_integral_v<>::value
  cout << std::boolalpha << std::is_integral<int>::value << endl;       // true
  cout << std::boolalpha << std::is_integral_v<decltype(die6)> << endl; // false
  cout << std::is_lvalue_reference_v<decltype(&die6)> << endl;          // false
  cout << std::is_pointer_v<decltype(&die6)> << endl;                   // true

  cout << GREEN << "typeid(variable).name() mangles the name" << endl;
  cout << RESET << typeid(i).name() << endl;
  cout << typeid(mt).name() << endl;
  cout << typeid(die6).name() << endl;

  cout << GREEN << "Printing with abi:__cxa_demangle in <cxxabi.h>" << endl;
  cout << RESET << type_name_demangled<int>() << endl;
  cout << type_name_demangled<std::mt19937>() << endl;
  cout << type_name_demangled<std::uniform_int_distribution<>>() << endl;

  cout << GREEN << "The above using decltype()" << endl;
  cout << RESET << type_name_demangled<decltype(i)>() << endl;
  cout << type_name_demangled<decltype(mt)>() << endl;
  cout << type_name_demangled<decltype(die6)>() << endl;

  cout << GREEN << "and again with macro" << RESET << endl;
  PRINT_TYPEVAL(i);
  PRINT_TYPEVAL(s);

  cout << GREEN << "Extracting type from __PRETTY_FUNCTION__" << endl;
  cout << RESET << type_name_from_pretty_function<decltype(i)>() << endl;
  cout << type_name_from_pretty_function<decltype(mt)>() << endl;
  cout << type_name_from_pretty_function<decltype(die6)>() << endl;

  // SFINAE / Concepts   Substitution Failure is not an Error
  // template <typename T>
  // concept Integral = std::is_integral_v<T>;
  //
  // template <Integral T> void foo(T val) { cout << val << "\n"; }
}
