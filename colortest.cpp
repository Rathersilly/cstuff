// TODO get this working as well as color-console
// should be able to dye strings
// complete the functions in namespace interface i think.
// Advantages: can chain functions.
// can have "using Hue:red;" etc
// use ruby create_color_headers.rb to create all the functions
//
//
// inspired by
// https://github.com/aafulei/color-console/blob/master/include/color.hpp which
// is just for windows
//
// see wikipedia.org/wiki/ANSI_escape_code#C0_control_codes
// and
// https://notes.burke.libbey.me/ansi-escape-codes/
#include <iostream>
#include <map>
#include <string>
/* #include <type_traits> */
#define INFO std::cout << "\t" << __PRETTY_FUNCTION__ << std::endl;
#define RESET "\033[0m"
#define BOLD "\033[1m"    /* Red */
#define RED "\033[31m"    /* Red */
#define GREEN "\033[32m"  /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m"   /* Blue */
using std::cout;
using std::string;
namespace hue {

/********** ANSI ESCAPE ANSI_CODES
ANSI escape codes  always start with \x1b, or \e, or \033. These all the same.
[ is CSI (Control Sequence Introducer), followed by a control sequence.
If you see \x1b[0;1;34m, you can read it like this:

\x1b[  # call a function
0;1;34 # function arguments (0, 1, 34)
m      # function name

In effect, this is m(0, 1, 34). Similarly, \x1b[A is just A().
**********/

// to make this map use char* instead of strings check out:
// https://stackoverflow.com/questions/1524356/c-deprecated-conversion-from-string-constant-to-char
/* std::map<char *, char *> ANSI_CODES2 = {{(char *)"reset", (char *)"\033[0m"},
 */
template <class T> class Color {};
std::map<std::string, std::string> Colors = {{"reset", "\e[0m"},
                                             {"red", "\e[31m"},
                                             {"green", "\e[32m"},
                                             {"yellow", "\e[33m"},
                                             {"blue", "\e[34m"}};
std::map<std::string, std::string> ANSI_CODES = {{"bold", "1"},
                                                 {"red", "31"},
                                                 {"green", "32"},
                                                 {"yellow", "33"},
                                                 {"blue", "34"}};

// https://en.cppreference.com/w/cpp/utility/variadic
template <class... Args> string es(Args... args) {
  INFO;
  string s;
  return s;
}
string reset() { return ANSI_CODES["reset"]; }
string red() { return ANSI_CODES["red"]; }
string green() { return ANSI_CODES["green"]; }
string yellow() { return ANSI_CODES["yellow"]; }
string blue(string c = "") { return Colors["blue"]; }
string bold(string c = "") { return Colors["bold"] + c; }
string color(string c) { return ANSI_CODES[c]; }

struct Hue {
  string esc = "\e[";
  string cmd = "m";

  string green = esc + ANSI_CODES["green"] + cmd;
  string bold = "";
} Hue;
} // namespace hue
using namespace hue;
int main(int argc, char **argv) {

  // Macros - the most concise way
  cout << YELLOW << "HELLO\n";
  cout << YELLOW << BOLD << "HELLO\n";
  // possible interfaces:
  // Struct Hue with green as a member
  cout << Hue.green << "asdf\n";
  // string es(string arg), possibly with variadic arguments
  /* cout << es("bold", "green") << "hithere\n"; */
  // string color(string arg)
  cout << color("red") << "red\n";
  // Hue::green() returning the correct escape code
  // has advantage of cout << bold(blue(fast_blink())) << "foo";
  cout << hue::green() << "green" << hue::reset() << std::endl;
  // use ruby to create all the functions

  cout << hue::blue() << "blue" << hue::reset() << std::endl;
  cout << hue::red() << "" << hue::reset() << std::endl;
  cout << hue::green() << "HIHIHI" << hue::reset() << std::endl;

  cout << hue::blue() << "does bold blue work?" << hue::reset();
  cout << hue::blue(hue::bold()) << "does bold blue work?" << hue::reset()
       << std::endl;
  cout << "\e[1;32m"
       << "Bold Green(order of args doesn' matter\n";
  cout << "\e[32;1m"
       << "also Bold Green\n";

  printf("\n");
  printf("\x1B[31mTexting\033[0m\t\t");
  printf("\x1B[32mTexting\033[0m\t\t");
  printf("\x1B[33mTexting\033[0m\t\t");
  printf("\x1B[34mTexting\033[0m\t\t");
  printf("\x1B[35mTexting\033[0m\n");

  printf("\x1B[36mTexting\033[0m\t\t");
  printf("\x1B[36mTexting\033[0m\t\t");
  printf("\x1B[36mTexting\033[0m\t\t");
  printf("\x1B[37mTexting\033[0m\t\t");
  printf("\x1B[93mTexting\033[0m\n");

  printf("\033[3;42;30mTexting\033[0m\t\t");
  printf("\033[3;43;30mTexting\033[0m\t\t");
  printf("\033[3;44;30mTexting\033[0m\t\t");
  printf("\033[3;104;30mTexting\033[0m\t\t");
  printf("\033[3;100;30mTexting\033[0m\n");

  printf("\033[3;47;35mTexting\033[0m\t\t");
  printf("\033[2;47;35mTexting\033[0m\t\t");
  printf("\033[1;47;35mTexting\033[0m\t\t");
  printf("\t\t");
  printf("\n");

  return 0;
}
