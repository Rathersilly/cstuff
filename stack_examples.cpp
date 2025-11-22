// Super simple stack algorithms
// see Srivistava DSAC++ ch 4
#include <algorithm>
#include <ios>
#include <iostream>
#include <ostream>
#include <stack>
#include <string>
using namespace std;

// reverse a string using a stack
string stack_reverse_string(const string &str) {
  stack<char> stk;
  string result;
  for (auto &c : str) {
    stk.push(c);
  }
  while (!stk.empty()) {
    result += stk.top();
    stk.pop();
  }
  return result;
}

// validate matching parantheses in a string using a stack
bool validate_parenthesis_expression(const string &str) {
  stack<char> stk;
  for (auto &c : str) {
    if (c == '(')
      stk.push(c);
    if (c == ')')
      stk.pop();
  }
  return stk.empty();
}

int main(int argc, char **argv) {

  string s = "hello there";
  string r = stack_reverse_string(s);
  cout << s << " " << r << endl;
  string r2{s.rbegin(), s.rend()}; //  ez way to create reversed string
  cout << s << " " << r2 << endl;
  string s2 = s;
  std::reverse(s.begin(), s.end()); // ez way to reverse string
  cout << s2 << endl;

  s = "(1+1)";
  cout << boolalpha << validate_parenthesis_expression(s) << endl;
  s = "(1+1*(2*(2*(3+4)+(2+3))))"; // ok
  cout << boolalpha << validate_parenthesis_expression(s) << endl;
  s = "(1+1*(2*2*(3+4)+(2+3))))"; // wrong
  cout << boolalpha << validate_parenthesis_expression(s) << endl;
}
