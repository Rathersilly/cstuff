// todo - learn about state
// find out if this would make a good queue
#include <color_macros.h>
#include <sstream>
#include <string>
/* #include <string_view> */
using namespace std;

int main(int argc, char *argv[]) {
  string s = "well hello there";
  stringstream ss;
  ss << s;
  // .str() outputs the sstream, (wont mutate ss)
  cout << ss.str() << endl;
  cout << ss.str() << endl;
  string s2;
  // >> puts first word from ss into s (wont mutate ss) (will overwrite s)
  ss >> s2;
  cout << s2 << endl;
  cout << ss.rdstate() << endl;
  // >> puts next word from ss into s (overwriting s)
  ss >> s2;
  cout << s2 << endl;
  ss >> s2;
  cout << ss.rdstate() << endl;
  cout << s2 << endl;
  cout << ss.rdstate() << endl;
  ss.clear(); // Clear state flags.
  cout << ss.rdstate() << endl;
  cout << ss.str() << endl;
  ss >> s2;
  ss >> s2;
  ss >> s2;
  cout << s2 << endl;
  cout << ss.rdstate() << endl;

  return 0;
}
