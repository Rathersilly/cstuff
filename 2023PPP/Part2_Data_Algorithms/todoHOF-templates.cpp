// STLavavej's Core C++ video 2 was big inspo for this wrt
// Template Arg Deduction
// TODO - add concepts/requirements, add pointer template examples

// Template typenamees must be defined in the header file - if you absolutely
// need another file, put the definitions in a .inl (inline) file, and #include
// it at the bottom of the header - with .cpp file you get linker error.
#include "my_helpers.h"
#include <color_macros.h>
#include <functional>
#include <list>
#include <type_traits>
#include <typeinfo> // for typeid(foo).base_data()
#include <vector>
using namespace my;
using namespace std;
// Template argument deduction:
// you pass template params from <> in function call, if they cant be deduced

// this is wrong - you dont need <> in the function def
// std::vector<B> list_to_vector<A,B>(const std::list<A> &lst) {

// correct
template <typename A, typename B>
std::vector<B> list_to_vector(const std::list<A> &lst) {
  std::vector<B> vec;
  for (auto a = lst.begin(); a != lst.end(); ++a) {
    vec.push_back(*a);
  }
  return vec;
}

// Template non-type parameter - is a constexpr
template <typename T, int size> class myarray {
private:
  T array_[size]; // size is contexpr - dont need to dynamically allocate it
public:
  myarray() {
    cout << "constructing a myarray<" << typeid(T).name() << ">" << endl;
  }
};
template <typename T, int size> void print(myarray<T, size> &array) {
  cout << "printing myarray" << endl;
}
//
// Partial Template Specialization - override print for certain types
// Note - can't partially specialize a member function - can achieve
// that effect by creating a specialized subclass.
template <int size> void print(myarray<char, size> &array) {
  cout << "Partial template specialization for printing myarray of chars!"
       << endl;
};

// Class Template Specialization - eg if we need to do something else for bool
template <int size> class myarray<bool, size> {
public:
  myarray() { cout << "constructing a specialized myarray<bool>" << endl; }
};

// Specializing member functions - don't need to specify entire class
template <typename T> class MyClass {
  void print() {}
};
template <> void MyClass<double>::print() { cout << "printing..." << endl; }

template <typename A> int addAA(A a, A b) {
  PFUN;
  return a + b;
}
template <typename A> int addAAref(A &a, A &b) {
  PFUN;
  return a + b;
}
template <typename A> int add(A a, A b) {
  PFUN;
  return a + b;
}
template <typename A, typename B> int add(A a, B b) {
  PFUN;
  return a + b;
}
template <typename A, typename B> int add(A &a, B &b) {
  PFUN;
  return a + b;
}
int add(char a,
        char b) = delete; // disallow this function with a particular type

// Function Template Specialization
// Preferred method: non-template function which is called if types match
int add(int a, long b) { return a + b; }
//
// alternatively create a specialized funtion template
template <>
int add<double>(
    double a,
    double b) { // template parameter is not variable, so nothing in <>
  cout << "this function template is specialized";
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

  // it WILL work though if you overload -> void purr(const T* ptr)
  // can also overload for regex, etc.

  // this will work, of course - declaring the literal a string
  purr("peppermint"s);

  char c1 = 'a';
  char c2 = 'b';
  // cant add 2 chars - we deleted function
  /* cout << add(c1, c2); */

  // constructing some templated classes
  myarray<int, 5> myarr;
  myarray<bool, 5> myboolarr;
  myarray<char, 5> mychararr;
  print(myarr);
  print(mychararr);

  auto lam = [n](int x) { cout << "lambda: " << n << endl; };
  lam(4);

  return 0;
}
