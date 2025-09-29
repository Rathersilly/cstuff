// NOTE: Function Objects (aka Functors) with a side of Lambdas
#include <algorithm>
#include <color_macros.h>
#include <cstdlib>
#include <functional> // std::function
#include <iostream>
using namespace std;

void print_int_vector(const vector<int> v) {
  for (auto &a : v)
    cout << a << " ";
  cout << endl;
}

// NOTE: a functor is a struct/class that has an operator()
// it can be passed to functions like std::sort
// it can contain state
template <typename T> class Add {
public:
  Add() {}
  T operator()(T a, T b) { return a + b; }
};

template <typename T> class CheckIfAbove {
  T value_; // in a lambda, this would be like [value_](){}

public:
  CheckIfAbove(T value) : value_{value} {}
  T operator()(T a, T b) { return a > value_ && b > value_; }
};

template <typename T, typename F> int binary_op(T a, T b, F fun) {
  return fun(a, b);
}
int main(int argc, char *argv[]) {
  Add<int> add;
  CheckIfAbove<int> check_if_above(0);
  int a = 1, b = 2;
  int x = 10;
  int y = 100;
  cout << add(a, b) << endl;

  // NOTE: Function objects that are used to specity the the meaning of key
  // operations of a general algorithm are often referred to as
  // policy objects (cf Strategy Pattern aka Policy Pattern)

  cout << binary_op(a, b, add) << endl; // <int> is deduced
  cout << binary_op<double>(a, b, add) << endl;
  cout << binary_op(a, b, check_if_above) << endl;
  cout << binary_op(-1, b, check_if_above) << endl;
  cout << "using lambda: "
       << binary_op(a, b, [&](int a, int b) { return a > 0 && b > 0; }) << endl;
  auto fun = [&](int a, int b) { return a > 0 && b > 0; };
  cout << "lambda stored: " << binary_op(a, b, fun) << endl;

  // NOTE:filling a vector with 9-0 using a lambda
  vector<int> vec(10);
  std::generate(vec.begin(), vec.end(),
                [i = 9]() mutable -> int { return i--; });

  // NOTE:another example: filling a vector with random #s
  vector<int> random_vec(10);
  std::generate(random_vec.begin(), random_vec.end(),
                []() { return rand() % 10; });
  print_int_vector(random_vec);

  // NOTE: std::sort with certain # first then evens then odds using a functor:
  struct WeirdComp {
    int num;
    WeirdComp(int n) : num{n} {}

    bool operator()(const int &a, const int &b) const {
      // cout << a << " " << b << endl;
      if (a == num)
        return true;
      if (b == num)
        return false;
      if (a % 2 == 0 && b % 2 == 0)
        return a < b;
      if (a % 2 == 0)
        return true;
      if (b % 2 == 0)
        return false;
      else
        return a < b;
    }
  };
  WeirdComp sevens_then_evens{7};

  cout << "sorting with sevens then evens first: " << endl;
  ;
  print_int_vector(vec);
  std::sort(vec.begin(), vec.end(), sevens_then_evens);
  print_int_vector(vec);

  // NOTE: Lambda Functions
  // [] is capture group - like the members of a function object
  // [&] capture ALL locals (passed by reference)
  // [=] capture ALL locals (passed by value)
  // [x, &y] capture the specified locals (by value or reference)
  // [&, x, y]   capture named vars by value, all others by reference
  // [=, &x, &y] capture named vars by reference, all others by value
  //
  // Capture group is like initializer list for a function object
  // Don't go overboard with capturing
  // - arg list is there for a reason (eg adding constness)
  //
  // () is parameter list
  // optional mutable/noexcept
  // optional ->return type

  auto fun_with_reference = [&](int a, int b) {
    x = 7;
    return a + b + x;
  };
  auto fun_with_value = [x, y](int a, int b) { return a + b + x + y; };
  cout << fun_with_value(a, b) << endl;
  cout << "x was not changed: " << x << endl;
  cout << fun_with_reference(a, b) << endl;
  cout << "x was changed in lambda: " << x << endl;

  // NOTE: auto is preferred when storing a lambda
  // - Each lambda has a unique type
  // - Naming a lambda is good for readability/self documentation
  // - Consider using std::function if you need a specific function type

  std::function<int(int, int)> foo = [&](int a, int b) {
    std::cout << "hi" << std::endl;
    return a + b;
  };

  // NOTE: A fuction object that captures/references variables from its
  // lexical scope is called a closure.
  // with mutable, we can manipulate a variable stored in closure

  auto fun_mutable = [x, &y]() mutable {
    x += 1; // increment the x that is local to the closure
    y += 1; // increment y, which is a reference to the y in main
    return x;
  };
  cout << GREEN << BOLD << "Mutating x in lambda and y in main:" << RESET
       << endl;
  cout << "fun_mutable x: " << fun_mutable() << endl;
  cout << "x: " << x << ", y: " << y << endl;
  cout << "fun_mutable x: " << fun_mutable() << endl;
  cout << "x: " << x << ", y: " << y << endl;
  cout << "fun_mutable x: " << fun_mutable() << endl;
  cout << "x in main is still: " << x << endl;

  // can omit () if empty
  auto fun_minimalist = [] { cout << "hi" << endl; };
  auto fun_very_minimalist = [] {};

  // optional return type -> int
  // unlike functions, lambdas can deduce return type
  auto fun_explicit_return = [](int a) -> int { return a * a; };
  fun_minimalist();
  fun_very_minimalist();
  cout << fun_explicit_return(3) << endl;

  // NOTE: you can use "this" in a lambda - leaving example for later mb

  // NOTE: Beware! A lambda can outlive it's caller
  // eg variables passed by reference may have been destroyed.
  //
  // NOTE: A lambda that captures nothing can be assigned to a
  // pointer to a function of an appropriate type

  int (*p)(int) = [](int a) { return a * a; };

  // NOTE: You can define a variable in []. change it with mutable keyword
  auto print_hi = [str = "hi"]() { cout << str << endl; };
  auto count = [i = 0]() mutable -> int { return i++; };
  cout << count() << endl; // 0
  cout << count() << endl; // 1

  struct Warrior {
    string name;
    string warcry;
  };
  auto print_warcry = [w{Warrior{"bob", "grr"}}]() {
    cout << w.warcry << endl;
  };
  print_warcry();

  return 0;
}
