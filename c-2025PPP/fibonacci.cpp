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
auto &now = std::chrono::high_resolution_clock::now;

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
  int cur_fib;
  for (int i = 2; i <= n; ++i) {
    cur_fib = a + b;
    a = b;
    b = cur_fib;
  }
  return cur_fib;
}

int fibrecursive(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return fibrecursive(n - 1) + fibrecursive(n - 2);
}

// fib_memoized: using a static vector to cache calculated results
int fib_memoized(std::size_t n) {
  static std::vector fibs{0, 1};

  // If we've already seen this n, then use the cache'd result
  if (n < std::size(fibs))
    return fibs[n];

  // Otherwise calculate the new result and add it
  fibs.push_back(fib_memoized(n - 1) + fib_memoized(n - 2));
  return fibs[n];
}

int fib_memoized_non_recursive(std::size_t n) {
  static std::vector fibs{0, 1};
  while (fibs.size() <= n) {
    fibs.push_back(fib(n));
  }
  return fibs[n];
}

int main() {

  int num = 40;
  int (*p)(int){&x2};

  cout << x2(3) << endl;
  cout << dofun(5, x2) << endl;
  // cout << dofun(5, {int(*)(int x ){return x}} << endl;
  // cout << dofun(5, std::function<int,int> fn =gg{
  //   return x;} << endl;

  // now() returns std::chrono::time_point

  // for (int i = 0; i < num; ++i) {
  //   cout << fib(i) << " ";
  // }
  cout << endl;
  auto t1 = high_resolution_clock::now();
  fib(num);
  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> diff_ms = t2 - t1;
  duration<double> diff_sec = t2 - t1;
  cout << "fib duration: " << diff_ms.count() << "ms" << endl;
  cout << "fib duration: " << diff_sec.count() << "sec" << endl;

  // for (int i = 0; i < num; ++i) {
  //   cout << fibrecursive(i) << " ";
  // }
  cout << endl;
  t1 = high_resolution_clock::now();
  fibrecursive(num);
  t2 = high_resolution_clock::now();
  diff_sec = t2 - t1;
  diff_ms = t2 - t1;
  cout << "fibrecursive duration: " << diff_ms.count() << "ms" << endl;
  cout << "fibrecursive duration: " << diff_sec.count() << "sec" << endl;

  /* Getting number of milliseconds as an integer. */
  // ms_int = duration_cast<milliseconds>(t2 - t1);

  /* Getting number of milliseconds as a double. */
  // duration<double, std::milli> diff_ms = t2 - t1;

  // std::cout << ms_int.count() << "ms\n";
  // std::cout << diff_ms.count() << "ms\n";

  t1 = high_resolution_clock::now();
  fib_memoized(num);
  t2 = high_resolution_clock::now();
  diff_ms = t2 - t1;
  cout << "fib memoized duration: " << diff_ms.count() << "ms" << endl;

  t1 = now();
  fib_memoized(num);
  t2 = now();
  diff_ms = t2 - t1;
  cout << "fib memoized 2nd duration: " << diff_ms.count() << "ms" << endl;
  // for (int count{0}; count < num; ++count)
  //   std::cout << fib_memoized(static_cast<std::size_t>(count)) << ' ';
  // cout << endl;
  t1 = high_resolution_clock::now();
  fib_memoized_non_recursive(num);
  t2 = high_resolution_clock::now();
  diff_ms = t2 - t1;
  cout << "fib_memoized_non_recursive duration: " << diff_ms.count() << "ms"
       << endl;

  t1 = now();
  fib_memoized_non_recursive(num);
  t2 = now();
  diff_ms = t2 - t1;
  cout << "fib_memoized_non_recursive 2nd duration: " << diff_ms.count() << "ms"
       << endl;
}
