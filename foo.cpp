#include <functional> // std:;function
#include <iostream>

int main() {
  int x = 0; // Assuming x is defined somewhere in your code

  auto fun_with_reference = [&](int a, int b) {
    // x = 7;
    // return a + b + x;
    return 1;
  };

  using LambdaType = decltype(fun_with_reference);

  LambdaType foo = [&](int a, int b) {
    x = 7;
    std::cout << "hi" << std::endl;
    return a; // Same return type as fun_with_reference
  };

  // Now you can call both lambdas
  std::cout << fun_with_reference(2, 3) << std::endl; // Outputs: 12
  std::cout << foo(42, 0) << std::endl;               // Outputs: hi\n42

  return 0;
}
