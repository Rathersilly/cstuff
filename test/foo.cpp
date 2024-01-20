#include <color_macros.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int add(int a, int b) { return a + b; }
int divide(int a, int b) { return a / b; }
template <typename T> bool assert(T a, string msg = "failed assertion") {
  if (!a) {
    cout << BOLD << RED << msg << RESET << endl;
    return false;
  } else {
    cout << BOLD << GREEN << "passed" << RESET << endl;
    return true;
  }
}

template <typename T>
bool assert_equal(T a, T b, string msg = "assert_equal_failed") {
  return assert(a == b, msg);
}
class TestBase {

  ;
};

class Test_add : TestBase {
  // need container of tests

  void run() {

    for (auto test : tests) {
      setup();
      test.run();
    }
  }

  void setup() {
    int a = 1;
    int b = 2;
  }
  void test_add() {
    // somehow call setup but with its variables local
    // pretty sure such hooks arent possible - just do it manually
    setup();
    assert_equal(add(1, 2), 3, "hihi");
  }
};

namespace TEST {
int a;
int b;

void setup() {
  a = 1;
  b = 2;
}
void test_add() {
  // somehow call setup but with its variables local
  setup();
  assert_equal(add(a, b), 3);
  assert_equal(add(a, b), 4);
}
} // namespace TEST

int main(int argc, char *argv[]) {

  assert(true, "hi");
  assert(false, "hi");
  assert_equal(add(1, 2), 3, "hihi");
  assert_equal(add(1, 2), 5, "NOPE");
  TEST::test_add();
  return 0;
}
