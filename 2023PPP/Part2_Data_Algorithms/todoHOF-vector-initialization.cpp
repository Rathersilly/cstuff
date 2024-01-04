// HOF TODO - how to initialize vectors

#include <iostream>
#include <vector>

using namespace std;

template <class T> void print_vector(vector<T> v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i];
  }
  cout << endl;
}
int main(int argc, char *argv[]) {
  /* vector<int> a(10, {1, 2, 3, 4}); */

  // create vector of size 2, default initialized to 1
  vector<int> v(2, {1}); // v is 11
  v.resize(4);           // v is 1100
  v.resize(6, {2});      // v is 110022
  v.resize(3);           // v is 110
  v.resize(6);           // v is 110000
  v.clear();             // v has size 0
  v.resize(6, {2});      // v is 222222
  return 0;
}
