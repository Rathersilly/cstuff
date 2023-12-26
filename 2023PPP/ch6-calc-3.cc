// Third calculator iteration-ch6
// Implementing Tokens
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
#define RESET "\033[0m"
#define RED "\033[31m"    /* Red */
#define GREEN "\033[32m"  /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m"   /* Blue */
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout, std::string; // more safe than using namespace std;
using namespace std;
enum Kind { number };

int main(int argc, char *argv[]) {
  cout << "Enter expression: ";
  int lval = 0;
  int rval;
  char op;
  int res;

  cin >> lval;
  if (!cin)
    throw runtime_error("no first operand");

  for (char op; cin >> op;) {
    if (op != 'x')
      cin >> rval;
    if (!cin)
      throw runtime_error("no second operand");
    switch (op) {
    case '+':
      lval += rval;
      break;
    case '-':
      lval -= rval;
      break;
    case '*':
      lval *= rval;
      break;
    case '/':
      lval /= rval;
      break;
    default:
      cout << "Result: " << lval << endl;
      return 0;
    }
    cout << BLUE << "running total: " << lval << RESET << endl;
  }
  throw runtime_error("bad expression");
}
