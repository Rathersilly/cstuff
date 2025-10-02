#include <chrono>
#include <functional>
#include <iostream>
#include <type_traits>

// --- 1. Normal function ---
int normal_fun(int x) { return x + 1; }

// --- 2. Virtual function example ---
struct Base {
  virtual int call(int x) = 0;
  virtual ~Base() = default;
};
struct Derived : Base {
  int call(int x) override { return x + 1; }
};

// Helper to measure runtime
template <typename F> void bench(const char *name, F f) {
  constexpr int N = 100000000; // 100 million
  auto start = std::chrono::high_resolution_clock::now();
  int sum = 0;
  for (int i = 0; i < N; ++i) {
    sum += f(i);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << name << ": " << elapsed.count() << "s (sum=" << sum << ")\n";
}

int main() {
  // 1. Normal function
  bench("normal function", [](int i) { return normal_fun(i); });

  // 2. Capturing lambda
  int offset = 1;
  auto lambda = [offset](int x) { return x + offset; };
  bench("lambda", lambda);

  // 3. Virtual function
  Derived d;
  Base *b = &d;
  bench("virtual function", [b](int x) { return b->call(x); });

  // 4. std::function
  std::function<int(int)> f = lambda;
  bench("std::function", f);
}
