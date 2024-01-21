#include <functional>
#include <iostream>
#include <vector>

#define PFUN std::cout << __PRETTY_FUNCTION__ << std::endl;
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

/* using namespace std; */
/* template <class T> void print_vector(const std::vector<T> &vec) { */
/*   for (const auto &elem : vec) { */
// /* std::cout << elem << " "; */
// /* } */
/* std::cout << std::endl; */
/* } */
// void foo(bool b = true) { cout << "foo"; }

int main(int argc, char *argv[]) {
  /* void (*myfun)(bool){&foo}; */
  /* std::function<void(bool)> myfun2{&foo}; */
  void (*myfun)(bool) = &foo;
  std::function<void(bool)> myfun2 = &foo;
  myfun();
  myfun2();
  return 0;
}
