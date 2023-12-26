
#include <iostream> // std::cin, std::cout
#include <string>   // std::cin, std::cout
using namespace std;

int main(int argc, char *argv[]) {
  string s;
  cin >> s;
  if (cin)
    cout << "cin";
  else if (!cin)
    cout << "!cin";

  return 0;
}
