#include <iostream>
#include <vector>

void copy(int *a, int *b, int *c) {
  while (a != b) {
    *c = *a;
    ++a;
    ++c;
  }
}
using namespace std;
int main(int argc, char *argv[]) {
  int a[]{1, 2, 3};
  cout << *a;
  cout << a[1];
  int *b = new int[3];
  copy(a, a + 2, b);
  cout << b[1];
  return 0;
}
