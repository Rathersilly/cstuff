// PPP ch 11 - Customizing IO
#include <fstream>
#include <iomanip> // setprecision(n), setw, fixed, etc
#include <iostream>
#include <string>
#include <vector>
#define LEFT std::left << std::setw(20)
using namespace std;

int main() {
  cout << showbase;
  // cout << noshowbase;
  //  dec/hex/oct states remain until changed
  cout << std::left << std::setw(20) << 1234 << "(decimal)\n"
       << LEFT << hex << 1234 << "(hexadecimal)\n"
       << LEFT << oct << 1234 << "(octal)\n";

  int a, b;
  
  // cin >> a >> hex >> b;
  // this will cout dec versions:
  // cout << a <<  b;
  //
  cout << LEFT << defaultfloat << 1234.56789 << "(defaultfloat)\n"
       << LEFT << fixed << 1234.56789 << "(fixed)\n"
       << LEFT << scientific << 1234.56789 << "(scientific)\n";

  cout << LEFT << defaultfloat << 1234.56789
       << "(defaultfloat)\n"; // prints 1234.56
  cout << LEFT << defaultfloat << 12.3456789
       << "(defaultfloat)\n"; // prints 12.3457 (rounded)
  cout << LEFT << defaultfloat << 123456789.0
       << "(converted to sci)\n"; // prints 1.23457e+08 (rounded)
  cout << LEFT << defaultfloat << setprecision(8) << 123456.7890
       << "(precision set to 8)\n"; // prints 123456.79 (rounded)
  cout << LEFT << fixed << setprecision(3) << 123456.7890
       << "(fixed prec 3 (3 after dec pt))\n"; // prints 123456.789 (rounded)

  // different number formats
  // will output 1234 1234 1234
  cout << dec << 1234 << "\t" << 0x4d2 << "\t" << 02322 << "\n";

  // setw won't truncate data
  cout << 123456 << '|' << setw(4) << 123456 << '|' << setw(8) << 123456 << '|'
       << 123456 << '|' << endl;
  cout << "asdfgh" << '|' << setw(4) << "asdfgh" << '|' << setw(8) << "asdfgh"
       << '|' << "asdfgh" << '|' << endl;

  // justifying columns
  cout << left << setfill('*') << setw(10) << "abc" << "\n";
  cout << right << setfill('*') << setw(10) << "abc" << "\n";
  cout << left << setfill('*') << setw(10) << "abc" << setw(10) << "abc" << setw(10) << "abc" << "\n";
  cout << left << setfill('*') << setw(10) << "abc" << setw(10) << "abcdefghijklmnop" << setw(10) << "abc" << "\n";
}
