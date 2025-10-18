#include <chrono>
#include <iostream>
using namespace std::chrono_literals;
using namespace std;

int main(int argc, char *argv[]) {
  std::chrono::duration<long long, std::nano> asdf{100};
  cout << asdf.count() << endl;
  cout << (asdf == 100ns) << endl;
}
code / cstuff / lib_examples / f
