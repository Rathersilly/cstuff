#include <algorithm> // std::shuffle, sort
#include <chrono>    // std::chrono::high_resolution_clock
#include <iostream>
#include <random> // std::mt19937, uniform_int_distribution
#include <vector>
using namespace std;

template <typename T> void print_vector(const vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  cout << endl;
}

using namespace std;
int main(int argc, char *argv[]) {

  // create prng generator using mersenne twister algorithm
  // can use std::mt19937(some seed),
  std::mt19937 mt{
      std::chrono::high_resolution_clock::now().time_since_epoch().count()};
  // a function to convert random number from a to b
  std::uniform_int_distribution<> die12{1, 12};
  std::uniform_int_distribution<> die10{1, 10};
  // note that die10 is the same as:
  cout << mt() % 10 << " " << die10(mt) << endl;

  // create a vector of 10 random 0-9
  vector<int> v1;
  for (int i = 0; i < 10; ++i) {
    v1.push_back(die10(mt));
  }
  print_vector(v1);

  // create a vector of 0-9, shuffled
  vector<int> v2;
  for (int i = 0; i < 10; ++i) {
    v2.push_back(i);
  }
  std::shuffle(v2.begin(), v2.end(), mt);
  // this also works, but unseeded
  std::shuffle(v2.begin(), v2.end(), std::mt19937());
  print_vector(v2);
  sort(v2.begin(), v2.end());
  print_vector(v2);

  // now() returns std::chrono::time_point<std::chrono::(whichever clock)>
  // time_since_epoch() returns std::chrono::duration since clocks epoch start
  // count() returns # of ticks in that duration
  cout << std::chrono::system_clock::now().time_since_epoch().count() << endl;
  cout << typeid(std::chrono::system_clock::now().time_since_epoch().count())
              .name();
}
