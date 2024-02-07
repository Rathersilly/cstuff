#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
using namespace std;

std::tuple<double, char, std::string> get_student(int id) {
  switch (id) {
  case 0:
    return {3.8, 'A', "Lisa Simpson"};
  case 1:
    return {2.9, 'C', "Milhouse Van Houten"};
  case 2:
    return {1.7, 'D', "Ralph Wiggum"};
  case 3:
    return {0.6, 'F', "Bart Simpson"};
  }

  throw std::invalid_argument("id");
}

template <typename... Args> void printTupleElements(const Args &...args) {
  ((std::cout << args << " "), ...);
}

template <std::size_t Index, typename... Args>
decltype(auto) getIndex(const std::tuple<Args...> &t) {
  return std::get<Index>(t);
}

int main() {
  // NOTE: Getting values from a tuple
  std::tuple<int, double, std::string> myTuple = {42, 3.14, "Hello"};
  // A: Structured Binding (C++ 17+)
  auto [a, b, c] = myTuple;
  std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;

  // A: std::apply (C++ 17+)
  std::apply(printTupleElements<int, double, std::string>, myTuple);
  std::cout << std::endl;

  // A: Index-based Access (C++14+)

  const auto student0 = get_student(0);
  std::cout << "ID: 0, "
            << "GPA: " << std::get<0>(student0) << ", "
            << "grade: " << std::get<1>(student0) << ", "
            << "name: " << std::get<2>(student0) << '\n';

  const auto student1 = get_student(1);
  std::cout << "ID: 1, "
            << "GPA: " << std::get<double>(student1) << ", "
            << "grade: " << std::get<char>(student1) << ", "
            << "name: " << std::get<std::string>(student1) << '\n';

  double gpa2;
  char grade2;
  std::string name2;
  std::tie(gpa2, grade2, name2) = get_student(2);
  std::cout << "ID: 2, "
            << "GPA: " << gpa2 << ", "
            << "grade: " << grade2 << ", "
            << "name: " << name2 << '\n';

  // C++17 structured binding:
  const auto [gpa3, grade3, name3] = get_student(3);
  std::cout << "ID: 3, "
            << "GPA: " << gpa3 << ", "
            << "grade: " << grade3 << ", "
            << "name: " << name3 << '\n';

  tuple<int, string, int> foo{1, "foo", 2};
  std::cout << get<0>(foo) << endl;
  std::cout << get<1>(foo) << endl;
  std::cout << get<2>(foo) << endl;
}
