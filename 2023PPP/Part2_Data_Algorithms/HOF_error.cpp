// TODO contains MyError class, and examples of throw and try/catch
#include <exception>
#define INFO                                                                   \
  cout << "\t"                                                                 \
       << "In function: " << __PRETTY_FUNCTION__ << endl;
#include <iostream>
#include <string>
/* #include <string_view> // c++17 */
#include <typeinfo>
using namespace std;
// from other hof error file

// These are the exceptions listed in the ISO standard:
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

// std::exception is a VERY barebones class
// it has constructor, operator= (assignment), and:
// virtual const char* what() const noexcept;
/* class MyError:std::exception{ */
// TODO relearn inheritance and make this work
class MyError : std::logic_error {
  // is default correct here?
  // super?

  // this defines two global instances of MyError (for demo purposes)
  // so can throw(myerror);
  // instead of throw(MyError{});
  /* } myerror, myerror2; */
};

void cause_error(char *msg = "Error (default args)") {
  INFO;
  // naked throw will end program with msg: "terminate called without an active
  // exception" throw;
  throw(out_of_range{msg});
  cout << "This line won't be executed" << endl;
}

// the callee should throw an exception - the caller should handle
double divide(double a, double b) {
  INFO;
  // zero division is not an exception in c++
  if (b == 0) {
    throw(logic_error("divide by zero"));
  }
  return a / b;
}

// TODO - make this prettier
void test() {
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
  /* throw(MyError{"hi"}); */
  /* throw(MyError( "hi" )); */
  /* throw(MyError()); */
  double a = 1, b = 0.0, c = 0.1;
  string s = "hello";
  constexpr int ccc = 5;

  // static_assert is a compile time assertion and it can't be caught
  static_assert(ccc != 3, "ITS NOT 3");

  try {
    cout << divide(3, 0) << endl;
  } catch (logic_error &e) {
    cout << RED << "caught exception with msg: " << e.what() << endl;
  } catch (...) { // catch every other error
    cout << RED << "caught other exception" << endl;
  }

  cout << GREEN << "continuing program" << RESET << endl;

  // can rethrow error after handling it - e.g. by plugging a memory leak
  try {

    cause_error();
  } catch (exception &e) {
    cout << "caught and rethrowing" << endl;
    // throw; // this will throw whatever is caught - we dont need to specify e
  }

  // can throw anything! ints, vectors, windows, you name it!
  // from https://en.cppreference.com/w/cpp/language/try_catch
  try {
    throw 42;
  } catch (int i) {
    cout << RED << "caught an integer: " << i << endl;
  }

  /* catch (logic_error) {} */
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
/*     throw std::exception(); // exception is the superclass of runtime_error.
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
/*               << std::endl; // e.what() will always just say "std::exception"
 */
/*   } catch (...) { */
/*     std::cout << "exception found: " */
/*               << std::endl; // e.what() will always just say "std::exception"
 */
/*   } */
/**/
/*   test(); */
/* } */
