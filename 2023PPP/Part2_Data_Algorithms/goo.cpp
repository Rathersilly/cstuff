#include <algorithm> //std::shuffle
#include <chrono>    // std::chrono::high_resolution_clock / system_clock
#include <color_macros.h>
#include <functional> // std::function
#include <initializer_list>
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
class mystring {
public:
  string s;

  mystring(initializer_list<string> lst) : s{*(lst.begin())} { PFUN; }
  mystring(string ss) : s{ss} { PFUN; }
  friend ostream &operator<<(ostream &os, mystring s);
  mystring operator()(int i) {
    mystring memo = s.substr(i);
    return memo;
  }
};
ostream &operator<<(ostream &os, mystring ss) {
  os << ss.s;
  return os;
}

int main(int argc, char *argv[]) {
  mystring str{"hello there"s};
  cout << str << endl;
  cout << str.s.substr(3) << endl;
  cout << str(3) << endl;

  return 0;
}
