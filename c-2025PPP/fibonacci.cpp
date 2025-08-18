#include "color_macros.h"
#include <chrono>
#include <iostream>
#include <vector>
#define INFO std::cout << "\t" << __PRETTY_FUNCTION__ << std::endl;
using namespace std;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int x2(int x) // code starts at memory address 0x002717f0
{
  return x * 2;
}
int dofun(int x, int (*fun)(int)) { return fun(x); }

int fib(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  int a = 0;
  int b = 1;
  int i = 1;
  int res = 0;
  while (i < n) {
    res = a + b;
    a = b;
    b = res;

    ++i;
  }
  return res;
}
int fibrecursive(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return fibrecursive(n - 1) + fibrecursive(n - 2);
}
int fib_memoized(std::size_t count) {
  // We'll use a static std::vector to cache calculated results
  static std::vector results{0, 1};

  // If we've already seen this count, then use the cache'd result
  if (count < std::size(results))
    return results[count];

  // Otherwise calculate the new result and add it
  results.push_back(fib_memoized(count - 1) + fib_memoized(count - 2));
  return results[count];
}

int main() {
  int (*p)(int){&x2};

  cout << x2(3) << endl;
  cout << dofun(5, x2) << endl;
  // cout << dofun(5, {int(*)(int x ){return x}} << endl;
  // cout << dofun(5, std::function<int,int> fn =gg{
  //   return x;} << endl;

  // now() returns std::chrono::time_point

  for (int i = 0; i < 15; ++i) {
    cout << fib(i) << " ";
  }
  cout << endl;
  auto t1 = high_resolution_clock::now();
  fib(20);
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  duration<double> sec_double = t2 - t1;
  cout << "fib duration: " << ms_double.count() << endl;
  cout << "fib duration: " << sec_double.count() << endl;

  for (int i = 0; i < 15; ++i) {
    cout << fibrecursive(i) << " ";
  }
  cout << endl;
  t1 = high_resolution_clock::now();
  fibrecursive(20);
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  cout << "fibrecursive duration: " << ms_double.count() << endl;

  /* Getting number of milliseconds as an integer. */
  // ms_int = duration_cast<milliseconds>(t2 - t1);

  /* Getting number of milliseconds as a double. */
  // duration<double, std::milli> ms_double = t2 - t1;

  // std::cout << ms_int.count() << "ms\n";
  // std::cout << ms_double.count() << "ms\n";

  t1 = high_resolution_clock::now();
  fib_memoized(static_cast<std::size_t>(15));
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  cout << "fib memoized duration: " << ms_double.count() << endl;

  t1 = high_resolution_clock::now();
  fib_memoized(static_cast<std::size_t>(15));
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  cout << "fib memoized 2nd duration: " << ms_double.count() << endl;
  for (int count{0}; count < 15; ++count)
    std::cout << fib_memoized(static_cast<std::size_t>(count)) << ' ';
  cout << endl;
}
