// Ch 20 exercises 5, 11 - only finished a few but this file has examples of

#include "my_vector.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace my {
/* class pvector : private my::vector {}; */
class pvector : vector {
  ~pvector() {
    for (auto a : elem) {
      delete[] a;
    }
  }
};
} // namespace my

int main(int argc, char *argv[]) {
  my::pvector p;

  return 0;
}
