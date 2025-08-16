#include <iostream>
#include <random>

inline std::mt19937 mt{ 1234 }; // fixed seed for reproducibility

int main() {
    std::cout << "Initial state:\n" << mt << "\n";

    mt(); // advance once
    std::cout << "After 1 mt():\n" << mt << "\n";

    mt(); mt(); // advance two more times
    std::cout << "After 3 total mt():\n" << mt << "\n";

    // Use uniform distribution to advance the engine further
    std::uniform_int_distribution<int> dist(0, 5);
    int val = dist(mt);
    std::cout << "After distribution call:\n" << mt << "\n";
    std::cout << "Distribution generated: " << val << "\n";
}

