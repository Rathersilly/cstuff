#include <iostream>
#include <string>

using std::cout, std::string; // safer than using namespace std,
                              // but requires c++17+

namespace Animals {}
enum Animal {
  dog, // = 0
  cat, // = 1
  wolf = 4,
  dragon = 7,
  num_animals // will = 8 - one more than the previous.

};

int main(int argc, char *argv[]) {
  string s = "hi";
  cout << num_animals;
  return 0;
}
