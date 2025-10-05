// test.h
// custom assertions for testing
// TODO: find a more elegant way to pass caller to assertions than
// void test_iterator(const char *str = __builtin_FUNCTION()) {

// TODO:also the assertions are numbered, not the tests - should change it
// - probably best to make a test class/assertion class
// - they have state to keep (function name, line number, etc)
// - test should have subheadings of assertions
// - set info level somewhere - config variable/file, test_foo(verbosity)

// TODO: generalize functions eg pass function to be tested.
// - dont need test_insertion_sort and test_selection_sort
#ifndef TEST_H
#define TEST_H

#include <algorithm>
#include <color_macros.h>
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo> // typid

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using namespace std::literals;

static int passed = 0;
static int failed = 0;
static int assertions = 0;

// NOTE: __builtin_FUNCTION() is a compiler specific macro. It returns
// function name as const char[], just like __FUNCTION__,
// but does not give warning (a good thing?)
// - It seems to work fine with g++ and clang++
// - It is being used here to pass the caller function name through the
// assertions in order to show up in the report
// - https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
//
// - alternatively, could use a macro and an impl function:
// #define assert_equal(a, b, msg) assert_equal_impl(a, b, msg, __func__)
// #define PASS_FUNC const char *str = __builtin_FUNCTION()

// caller should will return the test name eg test_push_back

inline void report(bool success, string msg = "",
                   string caller = __builtin_FUNCTION()) {
  if (success) {
    cout << BOLD << GREEN << assertions << ". " << caller << " passed. " << msg
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
    report(false, msg, caller);
    return false;
  } else {
    ++passed;
    ++assertions;
    report(true, msg, caller);
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

template <typename ExceptionType, typename Callable>
bool assert_throw(const ExceptionType &expect_exception, Callable callable,
                  string msg = "", string caller = __builtin_FUNCTION()) {
  try {
    callable();
  }

  catch (const ExceptionType &e) {
    msg = "Correct exception caught: "s + typeid(e).name() + " \"" +
          string(e.what()) + "\"";
    return assert(true, msg, caller);
  } catch (std::exception &e) {
    msg = "Wrong exception caught: "s + typeid(e).name() + " \"" +
          string(e.what()) + "\"";
    return assert(false, msg, caller);
  }
  msg = "No assertion thrown";
  return assert(false, msg, caller);
}

template <class Iterator, class Compare = std::less<>>
bool assert_sorted(Iterator first, Iterator last, Compare cmp = Compare{},
                   string msg = "", string caller = __builtin_FUNCTION()) {
  return assert(std::is_sorted(first, last, cmp), "", caller);
}

void test_results() {
  cout << "\t" << CYAN << BOLD << "Tests complete: " << endl;
  if (failed == 0 && passed > 0) {
    cout << "\t" << BOLD << GREEN << "All " << assertions << " tests passed."
         << RESET << endl;
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
