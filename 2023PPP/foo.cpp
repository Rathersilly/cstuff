#include <color_macros.h>
#include <iomanip> // setprecision(n), setw
#include <iostream>
#include <string>
#include <typeinfo> // for typeid(foo).name()
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  vector<int> v{99, 2, 3, 4, 5};
  cout << v.end() - v.begin();
  return 0;
}
