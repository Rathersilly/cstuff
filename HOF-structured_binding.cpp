// Structured Binding - assignment to variables from a pair/tuple/array
// useful for returning multiple values
// cf Modern C++ Cookbook ch 1
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

// Return multiple values from a function
// return type is deduced
std::tuple<int, std::string, double> find() { return {1, "marius", 1234.5}; }

// alternatively, can use auto to deduce from the other end
// prefer explicit return type and implicit return statement for clarity imo
auto minmax(int a, int b) {
  return ((a < b) ? std::pair{a, b} : std::pair{b, a});
}

struct foo {
  int id;
  std::string name;
};

int main(int argc, char *argv[]) {

  // Can even bind to data members of a class:
  foo f{42, "john"};
  auto [i, n] = f;
  auto &[ri, rn] = f;
  f.id = 43;
  std::cout << f.id << ' ' << f.name << '\n'; // 43 john
  std::cout << i << ' ' << n << '\n';         // 42 john
  std::cout << ri << ' ' << rn << '\n';       // 43 john

  // initializing variables from a returned tuple
  auto [minVal, maxVal] = minmax(7, 3);
  std::cout << minVal << ", " << maxVal << '\n';

  {
    // again, initializing variables from a returned tuple
    auto [id, name, score] = find();

    // can do so in an if/switch statement
    if (auto [id, name, score] = find(); score > 1000) {
      std::cout << name << '\n';
    }
  }

  {
    // this is also doable with std::tie()
    int id;
    string name;
    double score;
    std::tie(id, name, score) = find();
    if (score > 1000) {
      std::cout << name << '\n';
    }
  }

  std::map<int, std::string> m;
  {
    // it becomes an iterator to a std::pair
    auto [it, inserted] = m.insert({1, "one"});
    std::cout << "inserted = " << inserted << '\n'
              << "value = " << it->second << '\n';
  }

  int arr[3]{1, 2, 3};
  auto [q, w, e]{arr};

  int a, b;
  std::tuple tup{1, 2, 3};
  // can use std::ignore with tie but not with binding
  std::tie(a, std::ignore, b) = tup;

  // in c++26 we can discard with _
  // BUT currently _ is just a normal identifier so we cant reuse
  auto [_, t, y]{arr};
}
