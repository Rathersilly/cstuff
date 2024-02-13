// NOTE: First ETC file: interesting but not HOF
//
// NOTE: writing class and iterators with wrong functions to see
// if i can still use range for loop on them
//
// NOTE: Result: Yes! all you need is operators !=,*,++
// and you can use range for loop for your nefarious purposes
#include <ctime>
#include <iostream>
#include <random>
using namespace std;

class Foo {
public:
  class Iter {
    int *curr;

  public:
    int count;
    Iter() : count{0} {}
    int operator*() {
      cout << "hi from operator*()  count = " << count << endl;
      return *curr;
    }

    bool operator!=(Iter other) {
      cout << "hi from operator!=() count = " << count << endl;

      if (count > 4) {
        count = 0;
        return false;
      }
      return true;
    }
    Iter operator++() {
      ++count;
      cout << "hi from operator++() count = " << count << endl;
      return *this;
    }
  };
  Iter begin() {
    Iter i;
    cout << "hi from begin() count = " << i.count << endl;
    return i;
  }
  Iter end() {
    Iter i;
    cout << "hi from end() count = " << i.count << endl;
    return i;
  }
};

int main(int argc, char *argv[]) {
  cout << "Tricking range-for with wrong iterators!\n" << endl;
  std::srand(std::time(nullptr));
  Foo foo;
  for (auto a : foo) {
    cout << "ITERATING:" << endl;
  }

  return 0;
}
