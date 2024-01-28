// TODO: EVERYTHING
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  string foo;
  foo.insert(foo.begin(), 'h');
  foo.push_back('e');
  foo.append("llo world");
  assert(foo.size() == 11);
  foo.append(4, '*');
  foo.pop_back();

  cout << foo << endl; // "hello world**"
  foo.erase(5, 2);     // start at index 5, erase 2 chars;
  cout << foo << endl; // "helloorld**"
  foo.replace(9, 3, " or");
  foo += " whatever";
  cout << foo << endl; // "helloorld or whaterver"
  // append

  // pop_back();
  ;
  ;

  return 0;
}
