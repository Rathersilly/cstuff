// Pseudo-random number generation
// see also random.h (from learncpp) for how to seed with clock
#include "color_macros.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

using std::cout, std::endl, std::setw;

std::mt19937 _mt{std::random_device{}()};

template <typename N, typename Distribution, typename Generator>
void printRandoms(N n, Distribution dist, Generator gen = _mt) {
  for (int i = 0; i < 5; ++i) {
    cout << setw(3) << dist(gen);
  }
  cout << endl;
}

int main() {

  // std::default_random_engine is usually minstd_rand
  // std::random_device is simiplest seed - uses /dev/random or /dev/urandom
  std::default_random_engine rd{std::random_device{}()};

  // std::mt19937 mersenne twister is solid recommended prng engine
  std::mt19937 mt{std::random_device{}()};

  cout << "rd() and mt() return std::uint_fast32_t " << endl;
  cout << rd() << " " << mt() << endl;

  std::uniform_int_distribution<int> die6(1, 6);
  std::uniform_int_distribution die12{1, 12}; // <int> is default
  printRandoms(5, die6, mt);
  printRandoms(5, die12, mt);

  // uniform int distribution
  int min = 0, max = 9, iterations = 1000;
  cout << GREEN << "uniform distribution, min: " << min << ", max: " << max
       << RESET << endl;
  std::uniform_int_distribution uniform_ten{min, max};
  std::map<int, int> uniform_hist{};
  for (int i = 0; i < iterations; ++i) {
    ++uniform_hist[uniform_ten(mt)];
  }
  for (auto [k, v] : uniform_hist) {
    cout << k << " " << std::string(v, '*') << endl;
  }

  // normal distribution
  double mean = 5;
  double stddev = 5;
  std::normal_distribution<double> normal_ten(mean, stddev);
  std::map<int, int> normal_hist{};
  for (int i = 0; i < iterations; ++i) {
    ++normal_hist[normal_ten(mt)];
  }
  cout << GREEN << "normal distribution, mean: " << mean
       << ", stddev: " << stddev << RESET << endl;
  for (auto [k, v] : normal_hist) {
    cout << k << " " << std::string(v, '*') << endl;
  }
}
