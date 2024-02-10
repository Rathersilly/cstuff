#include <functional> // std:;function
#include <iostream>
using namespace std;
// Primary template (undefined)
template <typename... Types> struct mytuple;

template <> struct mytuple<> {
  mytuple() {}
};
template <typename T1> struct mytuple : mytuple<> {
  T1 x;
  using Base = mytuple<>;
  Base *base() { return static_cast<Base *>(this); }
  const Base *base() { return static_cast<const Base *>(this); }

  mytuple(const T1 &t1) : Base{}, x{t1} {}
};
//
// // template <typename T1, typename T2 = T1, typename T3 = T2, typename T4 =
// T3> template <typename T1, typename T2, typename T3, typename T4> struct
// Tuple : Tuple<T2, T3, T4> {
//   T1 x;
//   using Base = Tuple<T2, T3, T4>;
//   Base *base() { return static_cast<Base *>(this); }
//   const Base *base() { return static_cast<const Base *>(this); }
//
//   Tuple(const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
//       : Base{t2, t3, t4}, x{t1} {}
// };
//
// int main(int argc, char *argv[]) {
//   Tuple<double, int, char> x{1.1, 42, 'a'};
//   cout << x << endl;
//   cout << get<1>(x) << endl;
//
//   return 0;
// }
