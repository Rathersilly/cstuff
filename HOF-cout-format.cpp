// PPP ch 11 - Customizing IO
#include <fstream>
#include <iomanip> // setprecision(n), setw, fixed, etc
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  cout << showbase;
  // cout << noshowbase;
  //  dec/hex/oct states remain until changed
  cout << 1234 << "\t(decimal)\n"
       << hex << 1234 << "\t(hexadecimal)\n"
       << oct << 1234 << "\t(octal)\n";
  // will output 1234 1234 1234
  cout << dec << 1234 << "\t" << 0x4d2 << "\t" << 02322 << "\n";

  int a, b;
  //
  // cin >> a >> hex >> b;
  // this will cout dec versions:
  // cout << a <<  b;
  //
  cout << defaultfloat << 1234.56789 << "\t\t(defaultfloat)\n"
       << fixed << 1234.56789 << "\t\t(fixed)\n"
       << scientific << 1234.56789 << "\t\t(scientific)\n";

  cout << defaultfloat << 1234.56789
       << "\t\t(defaultfloat)\n"; // prints 1234.56
  cout << defaultfloat << 12.3456789
       << "\t\t(defaultfloat)\n"; // prints 12.3457 (rounded)
  cout << defaultfloat << 123456789.0
       << "\t(converted to sci)\n"; // prints 1.23457e+08 (rounded)
  cout << defaultfloat << setprecision(8) << 123456.7890
       << "\t(precision set to 8)\n"; // prints 123456.79 (rounded)
  cout << fixed << setprecision(3) << 123456.7890
       << "\t(fixed prec 3 (3 after dec pt))\n"; // prints 123456.789 (rounded)

  // setw won't truncate data
  cout << 123456 << '|' << setw(4) << 123456 << '|' << setw(8) << 123456 << '|'
       << 123456 << '|' << endl;
  cout << "asdfgh" << '|' << setw(4) << "asdfgh" << '|' << setw(8) << "asdfgh"
       << '|' << "asdfgh" << '|' << endl;
}
