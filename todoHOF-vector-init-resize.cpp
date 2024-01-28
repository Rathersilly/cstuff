// HOF TODO - how to initialize vectors
// TODO: make sure my::vector has all these abilities

#include "2023PPP/Part2_Data_Algorithms/my_vector.h"
// #include "~/cstuff/my_helpers.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T> void print_vector(vector<T> v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i];
  }
  cout << endl;
}

template <typename T> // print vector fn from learncpp
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
  s.put('{');
  for (char comma[]{'\0', ' ', '\0'}; const auto &e : v)
    s << comma << e, comma[0] = ',';
  return s << "}\n";
}

int main(int argc, char *argv[]) {
  // Vector Constructors:
  // Initializer List
  vector<int> a{1};     // {1}
  vector<int> aa{1, 2}; // {1,2}
  std::vector<std::string> words1{"the", "frogurt", "is", "also", "cursed"};
  std::cout << "1: " << words1;

  // Iterator Range - words2 == words1
  std::vector<std::string> words2(words1.begin(), words1.end());
  std::cout << "2: " << words2;

  // Copy Ctor - words3 == words1
  std::vector<std::string> words3(words1);
  std::cout << "3: " << words3;

  // Init size (with uninitialized values)
  std::vector<std::string> bb(5);
  std::cout << bb; // {, , , ,}
  // Init size and default value
  std::vector<std::string> words4(5, "Mo");
  std::cout << "4: " << words4; // {"Mo", "Mo", "Mo", "Mo", "Mo"}

  // auto works with vector init list - interesting but trivial
  auto const rg = {"cat", "cow", "crow"};

#ifdef __cpp_lib_containers_ranges                      // c++ 23 i think
  std::vector<std::string> words5(std::from_range, rg); // overload (11)
#else
  std::vector<std::string> words5(rg.begin(), rg.end()); // overload (5)
#endif
  std::cout << "5: " << words5;

  /* vector<int> a(10, {1, 2, 3, 4}); */

  // create vector of size 2, default initialized to 1
  vector<int> v(2, {1}); // v is 11
  v.resize(4);           // v is 1100
  v.resize(6, {2});      // v is 110022
  v.resize(3);           // v is 110
  v.resize(6);           // v is 110000
  v.clear();             // v has size 0
  v.resize(6, {2});      // v is 222222

  // this will call myvector(initializer_list<int>)
  // but if that constructor doesnt exist,
  // it will call myvector(int)
  my::vector<int> myvec{1};
  // this will ofc call myvector(initializer_list<int>)
  my::vector<int> myvec2{1, 2};
  return 0;
}
