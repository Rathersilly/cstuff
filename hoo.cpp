#include <color_macros.h>
#include <queue>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

using namespace std;
int main(int argc, char *argv[]) {
  queue<char> buf;
  buf.push('c');
  buf.push('d');
  buf.push('e');
  char cmd = buf.front();
  cout << cmd;
  cmd = buf.front();
  cout << cmd;
  /* char cmd = buf.pop(); */
  /* queue<int> buf; */
  /* queue<int> buf2{1, 2, 3}; */
  /* int cmd2; */
  /* cmd2 = buf2.pop(); */
  return 0;
}
