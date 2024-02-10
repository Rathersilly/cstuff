#include <algorithm>  //std::shuffle
#include <chrono>     // std::chrono::high_resolution_clock / system_clock
#include <functional> // std::function
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>
using namespace std;
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) {
  if (b == 0)
    throw std::invalid_argument("cant divide by zero");
  return a / b;
}

int main(int argc, char *argv[]) {
  int a, b;
  char op;
  cout << "please enter 2 numbers and an operation (+, -, *, /)" << endl;
  cin >> a >> b >> op;
  cout << "you entered: " << a << b << op << endl;

  std::function<int(int, int, char)> ArithmeticFunction = [](int a, int b,
                                                             char op) {
    std::function<int(int, int)> fun;
    switch (op) {
    case '+':
      fun = &add;
      break;
    case '-':
      fun = &subtract;
      break;
    case '*':
      fun = &multiply;
      break;
    case '/':
      fun = &divide;
      break;
    }
    return fun(a, b);
  };
  cout << ArithmeticFunction(a, b, op);

  return 0;
}
