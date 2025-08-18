#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

using std::cout, std::endl, std::setw;

std::mt19937 mt{std::random_device{}()};
// function to print
template <typename N, typename T, typename U>
void printRandoms(N n, T t, U u = mt) {
  cout << n << "random numbers from " << typeid(t).name() << " using "
       << typeid(u).name() << endl;
  for (int i = 0; i < 5; ++i) {
    cout << setw(3) << t(u);
  }
  cout << endl;
}

int main() {
  // simplest seeded prng engine - uses /dev/random or /dev/urandom
  std::mt19937 mt{std::random_device{}()};
  // usage:

  cout << "hi" << endl;

  int a = mt();
  // or
  std::uniform_int_distribution die6(1, 6);
  std::uniform_int_distribution die12{1, 12};
  printRandoms(5, die6, mt);
  printRandoms(5, die12, mt);
}
