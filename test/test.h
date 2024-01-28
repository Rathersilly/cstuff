// test.h
// custom assertions for testing
#ifndef TEST_H
#define TEST_H

#include <color_macros.h>
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

static int passed = 0;
static int failed = 0;
static int assertions = 0;

inline void report(bool success, string caller, string msg = "") {
  if (success) {
    cout << BOLD << GREEN << assertions << ". " << caller << " passed. "
         << RESET << endl;
  } else {
    cout << BOLD << RED << assertions << ". " << caller << " failed: " << msg
         << RESET << endl;
  }
}

template <typename T>
bool assert(T a, string msg = "", string caller = __builtin_FUNCTION()) {
  if (!a) {

    ++failed;
    ++assertions;
    report(false, caller, msg);
    return false;
  } else {
    ++passed;
    ++assertions;
    report(true, caller, msg);
    return true;
  }
}

template <typename T>
bool assert_equal(T a, T b, string msg = "",
                  string caller = __builtin_FUNCTION()) {

  stringstream local_msg;
  if (a != b)
    local_msg << "Expected " << a << " = " << b << "\n";
  return assert(a == b, local_msg.str() + msg, caller);
}

template <typename T>
bool assert_equal_containers(T a, T b, string msg = "",
                             string caller = __builtin_FUNCTION()) {
  stringstream local_msg;
  if (a.size() != b.size()) {
    local_msg << "Container sizes differ: " << a.size() << " != " << b.size()
              << "\n";
    return assert(false, local_msg.str() + msg, caller);
  }

  auto a_iter = a.begin();
  auto b_iter = b.begin();
  while (a_iter != a.end()) {
    if (*a_iter != *b_iter) {
      local_msg << "Containers differ: " << *a_iter << " != " << *b_iter
                << "\n";
      return assert(false, local_msg.str() + msg, caller);
    }
    ++a_iter;
    ++b_iter;
  }
  return assert(true, msg, caller);
}
void test_results() {
  cout << "\t" << CYAN << BOLD << "Tests complete: " << endl;
  if (failed == 0 && passed > 0) {
    cout << "\t" << BOLD << GREEN << "All " << assertions << " " << passed
         << " tests passed." << RESET << endl;
    /* cout << "\t" << BOLD << GREEN << RAPID_BLINK << "GREAT JOB!" << RESET
     */
    cout << "\t" << BOLD << GREEN << "GREAT JOB!" << RESET << endl;
  } else {

    cout << "\t" << BOLD << GREEN << passed << " tests passed." << RESET
         << endl;
    cout << "\t" << BOLD << RED << failed << " tests failed." << RESET << endl;
  }
}
#endif
