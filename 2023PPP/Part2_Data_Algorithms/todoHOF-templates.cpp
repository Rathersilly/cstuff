// STLavavej's Core C++ video 2 was big inspo for this wrt
// Template Arg Deduction
// TODO - add concepts/requirements

#include "my_helpers.h"
#include <color_macros.h>
#include <functional>
#include <list>
#include <type_traits>
#include <vector>
using namespace my;
using namespace std;
// Template argument deduction:
// you pass template params from <> in function call, if they cant be deduced

// this is wrong - you dont need <> in the function def
// std::vector<B> list_to_vector<A,B>(const std::list<A> &lst) {

// correct
template <class A, class B>
std::vector<B> list_to_vector(const std::list<A> &lst) {
  std::vector<B> vec;
  for (auto a = lst.begin(); a != lst.end(); ++a) {
    vec.push_back(*a);
  }
  return vec;
}

template <class A> int addAA(A a, A b) {
  PFUN;
  return a + b;
}
template <class A> int addAAref(A &a, A &b) {
  PFUN;
  return a + b;
}
template <class A> int add(A a, A b) {
  PFUN;
  return a + b;
}
template <class A, class B> int add(A a, B b) {
  PFUN;
  return a + b;
}
template <class A, class B> int add(A &a, B &b) {
  PFUN;
  return a + b;
}

// compiler won't look past :: to deduce type, eg:
template <typename T> void meow(typename make_unsigned<T>::type t) {
  typedef typename make_unsigned<T>::type U;
  U u = static_cast<U>(t);
  cout << u << endl;
}
template <typename T> void meowfunction(T val, function<void(T)> f) { f(val); }

// weird struct that allows template function to accept lambda
// see STLavavej's c++ core part 2 ~50:00
template <typename T> struct Identity {
  typedef T type;
};
template <typename T>
void meowfunction_that_accepts_lambda(
    T val, typename Identity<function<void(T)>>::type f) {
  f(val);
}
template <typename T> void purr(const basic_string<T> s) { cout << s << endl; }

int main(int argc, char *argv[]) {

  std::list<int> lint{1, 2, 3, 4, 5};
  std::vector<double> vdouble = list_to_vector<int, double>(lint);
  vdouble = list_to_vector<int, double>(lint);
  print_vector(vdouble);

  const int a = 1;
  int b = 3;
  // these are all deduced just fine
  cout << add(1, 3) << endl;  // int(*)(A,A)
  cout << add(1, 3L) << endl; // int(*)(A,B)
  // convert b to double explicitly
  cout << add<int, double>(a, b) << endl; // int(*)(A,B)

  // const can be removed if we pass by value
  cout << add(a, b) << endl; // int(*)(A,B)
  // here we pass by ref;
  // params and args arent in agreement over constness, so error
  /* cout << addAAref(a, b) << endl; */

  // deduction fails: 2 different answers for A
  // compiler won't widen or narrow - makes you choose
  /* cout << addAA(1, 3L) << endl; */

  int n = -1234;
  // must be explicit here - deduction doesnt occur through ::
  meow<int>(n);

  // meowfunction will deduce this function arg just fine
  function<void(int)> fxn = [](int x) { cout << "lambda: " << x << endl; };
  meowfunction(4567, fxn);
  // but it won't from a lambda - lambdas are their own type
  /* meowfunction(4567, [](int x) { cout << "lambda: " << x << endl; }); */

  // there is a weird trick to make it work though - use :: barrier
  // and some weird metaprogramming - see fn def above
  meowfunction_that_accepts_lambda(
      4567, [](int x) { cout << "lambda: " << x << endl; });

  string s = "peppermint";
  // this works - string can be deduced to basic_string<string>
  purr(s);
  // this doesn't work - cant convert const char* literal to basic_string<T>
  /* purr("peppermint"); */

  // it WILL work though if you overload void purr(const T* ptr)
  // can also overload for regex, etc.

  // this will work, of course - declaring the literal a string
  purr("peppermint"s);

  auto lam = [n](int x) { cout << "lambda: " << n << endl; };
  lam(4);

  return 0;
}
