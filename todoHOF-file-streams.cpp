#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Ch8 of C++ Primer

void process_input(istream &input) {
  int x = 0;
  // input >> x;
  // cout << x << endl;
}

int main() {

  auto old_state = cin.rdstate();
  cin.clear();
  process_input(cin);
  process_input(cin);
  cin.setstate(old_state);
  cin.clear();
  // entering letters earlier will not work now - setstate didnt appear to work
  process_input(cin);

  ifstream in("nums.txt");
  ofstream out("output.txt");
  int num = 0;
  while (in >> num) {
    out << num << endl;
  }
  out.close();
  out.open("output2.txt");
  while (in >> num) {
    out << num << endl;
  }
  out.close();

  // fstream
  //
}
