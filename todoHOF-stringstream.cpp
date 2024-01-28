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
  // .str() gets or sets the contents of the underlying string device object
  // .view() returns view of underlying string device object
  ss.str("hi");

  ss << s;
  // .str() outputs the sstream, (wont mutate ss)
  cout << ss.str() << endl;
  string s2;
  // >> puts first word from ss into s (wont mutate ss) (will overwrite s)
  ss >> s2;
  cout << s2 << endl;
  // rdbuf() returns the underlying raw string device object

  // TODO show functions from superclasses
  // list superclasses - combine with general iostream HOF
  // ie where is rdstate()?
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
  // from lazyfoo22 - timing
  std::stringstream timeText;
  timeText.str("");
  // timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;
  // if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(),
  // textColor)) {

  return 0;
}
