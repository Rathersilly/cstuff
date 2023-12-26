// First calculator iteration- ch6p179)
//
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cout, std::string; // more safe than using namespace std;
using namespace std;

int main(int argc, char *argv[]) {
  cout << "Enter expression: ";
  int lval = 0;
  int rval;
  char op;
  int res;

  cin >> lval >> op >> rval;
  if (op == '+')
    res = lval + rval;
  else if (op == '+')
    res = lval - rval;

  cout << "Result: " << res << endl;
  return 0;
}
