#include "my_unique_ptr.h"
#include "my_helpers.h"
#include <color_macros.h>
#include <memory>
#include <utility>

int main(int argc, char *argv[]) {
  {
    vector<int> vec{1, 2, 3};
    auto pvec = std::make_unique<vector<int>>(3, 2);
    my::print_vector(*pvec);
    auto mypvec = my_unique_ptr(new vector<int>);
    mypvec->push_back(0);
    my::print_vector(*mypvec);
  }

  return 0;
}
