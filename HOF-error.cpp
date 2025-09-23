// Exceptios, MyError class, and examples of throw and try/catch
#include "color_macros.h"
#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// These are the exceptions listed in the ISO standard:
// They are found in <stdexcept>, although they seem to work with just
// <exception> -- that's compiler discretion. Include <stdexcept> for safety.
namespace std {
class logic_error;
class domain_error;
class invalid_argument;
class length_error;
class out_of_range;
class runtime_error;
class range_error;
class overflow_error;
class underflow_error;
} // namespace std

// std::exception is a VERY barebones class, only containing
// operator= (assignment)
// and virtual const char* what() function
// Derived classes like std::logic_error can be constructed with a string
// which will be returned by what()
class MyError : public std::logic_error {

  std::string what_message{};

public:
  MyError(const char *msg, const char *func = "Unknown")
      : std::logic_error(msg),
        what_message(string{"hello from overrided what()\n\tFunction: "} +
                     func + "\n\tMessage:  " + msg) {}

  virtual const char *what() const noexcept override {
    return what_message.c_str();
  }

  // Function try block example:
  MyError() try : std
    ::logic_error("default"), what_message{"default"} {

      // function body
    }
  catch (...) { // catch}
    // will catch exceptions when constructing base classes as well
    // (...) will catch all exceptions, but will not let you access them
  }
};

// Function try block
class A {
public:
  int m_id;

  A(int id)
  try : m_id{id} {
  };

  // Best practice: the callee should throw an exception, and the caller should
  // handle it. The callee may catch only if it can resolve the problem itself.
  double divide(double a, double b) {
    INFO;
    // floating-point division by zero does not throw (returns inf/nan).
    // Integer division by zero is undefined behavior.
    // Here, we choose to treat division by zero as a logic error.
    if (b == 0) {
      // Since this throw is not inside a try block, execution jumps up the
      // stack until it finds a matching catch, or the program terminates. This
      // process ("stack unwinding") destroys all local objects as usual by
      // calling their destructors. Beware: it may skip over important cleanup
      // if you're using raw new/delete, so prefer RAII types (std::unique_ptr,
      // std::vector, etc.).
      throw logic_error("divide by zero");
    }

    return a / b;
  }

  // TODO - make this prettier
  void risky_operation() {
    int a[]{1, 2, 3};
    try {
      a[4] = 5;
      cout << "hi" << endl;
      throw(std::length_error{"hi from test()"});
    } catch (std::length_error &e) {
      cout << "test failed: length error\n";
      throw; // rethrow
    } catch (std::bad_alloc &e) {
      // Ouch! test() is not designed to handle memory exhaustion
      std::terminate(); // terminate the program
    }
  }
  int main() {
    // throw(MyError{"THIS MESSAGE", __func__});

    // You can throw anything! ints, vectors, windows, you name it!
    try {
      throw 42;
    } catch (int i) {
      cout << RED << "caught an integer: " << i << endl;
    }

    double a = 1, b = 0.0, c = 0.1;
    string s = "hello";
    constexpr int ccc = 5;

    // Assertions - they do not throw exceptions
    // compile time assertion it can't be caught
    static_assert(ccc != 3, "ITS NOT 3");

    // runtime assert - requires <cassert>
    // assert is a macro that will eventually call std::abort() on failure
    assert(a == 1);

    // some actions will automatically throw
    try {
      cout << divide(3, 0) << endl; // divide by zero throws logic_error
    } catch (logic_error &e) {
      cout << RED << "caught exception with msg: " << e.what() << endl;
    } catch (...) { // catch every other error
      cout << RED << "caught other exception" << RESET << endl;
    }

    // cout << GREEN << __FILE__ << RESET << endl;
    // cout << GREEN << __LINE__ << RESET << endl;
    // cout << GREEN << __func__ << RESET << endl;
    cout << GREEN << "continuing program" << RESET << endl;

    // can rethrow error after handling it
    // e.g. by logging, releasing a resource, etc.
    try {

      throw runtime_error("OH NO");
    } catch (exception &e) {

      // here we can output to log, etc.
      cout << "caught and rethrowing." << e.what() << endl;
      throw; // this throws the caught object

    } catch (...) { // (exception &e) {
      cout << "this catch won't catch the rethrow - need a nested try block to "
              "do that."
           << endl;
    }

    // If an exception is not caught, std::terminate() is called, which will
    // then call std::abort(), which sends SIGABRT neither will clean anything
    // up
  }
  /**/
  /*   cout << endl; */
  /*   try { */
  /*     cause_error(); */
  /*   } catch (...) { */
  /*     cout << "caught error" << endl; */
  /*   } */
  /*   try { */
  /*     throw MyErrorClass(); */
  /*   } catch (MyErrorClass) { */
  /*     cout << "hey whats up" << endl; */
  /*   } */
  /*   cout << endl; */
  /*   try { */
  /*     throw std::exception(); // exception is the superclass of
   * runtime_error.
   */
  /*                             // exception() can't take a string argument */
  /*     throw std::runtime_error("HI"); */
  /*   } catch (std::runtime_error e) { */
  /*     std::cout << "runtime error found: " << e.what() */
  /*               << std::endl; // e.what() contains "HI" */
  /**/
  /*     return 0; */
  /*   } catch (std::exception e) { */
  /*     std::cout << "exception found: " << e.what() */
  /*               << std::endl; // e.what() will always just say
   * "std::exception"
   */
  /*   } catch (...) { */
  /*     std::cout << "exception found: " */
  /*               << std::endl; // e.what() will always just say
   * "std::exception"
   */
  /*   } */
  /**/
  /*   test(); */
  /* } */
