#include <iostream>
#include <random>

int main() {
  std::random_device rd;
  std::cout << "Entropy: " << rd.entropy() << "\n";
  std::cout << "Random number: " << rd() << "\n";
}
