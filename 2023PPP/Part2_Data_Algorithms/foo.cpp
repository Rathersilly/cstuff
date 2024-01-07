#include "color_macros.h"
#include "vector.h"

vector<int> make_vector(int i) {
  PFUNGREEN
  vector<int> v{i};
  return v;
}

vector<int> mv_vector_demo(vector<int> a) {
  PFUNGREEN
  return a;
}

int main(int argc, char *argv[]) {
  // testing constructors
  cout << GREEN << "Testing Constructors" << RESET << endl;
  vector<int> asdf;       // default
  vector<int> v(4);       // args
  vector<int> a{1, 2, 3}; // init list
  print_vector<int>(v);
  print_vector<int>(a);

  cout << GREEN << "copy ctor" << RESET << endl;
  vector<int> b(a); // copy constructor

  cout << GREEN << "also copy ctor" << RESET << endl;
  vector<int> bb = a; // copy ctor
  cout << GREEN << "copy assignment " << RESET << endl;
  bb = a; // copy assignment

  cout << BLUE << BOLD << "Testing move constructor " << RESET << endl;
  // These may only call copy constructor
  // compiler uses copy elision to elide the move constructor
  // observe this behavior with g++ -fno-elide-constructors
  vector<int> x = make_vector(4);
  x = make_vector(4);
  vector<int> y{make_vector(4)};
  vector<int> yy{mv_vector_demo(a)};

  cout << BLUE << BOLD << "moving with std::move" << RESET << endl;
  vector<int> z = std::move(y); // move constructor
  z = std::move(y);             // move assignment

  cout << GREEN << "Testing Access" << RESET << endl;
  b[1] = 7; // T &operator[]
  const vector<int> cv{1};
  const int ci = cv[0]; // const T &operator=

  int foo = a.at(0);
  // will correctly throw std::range_error
  /* int bar = a.at(5); */
  return 0;

  cout << GREEN << "Testing Space" << RESET << endl;
  vector<int> *c = new vector<int>;
  delete c;
  std::cout << v[1];
  v[1] = 12;
  std::cout << v[1];
  cout << "here" << endl;
  const vector<int> d{1, 2, 3};
  int e = d[2];
  cout << a.size() << endl;
  cout << a.capacity() << endl;
  a.reserve(20);
  cout << a.size() << endl;
  cout << a.capacity() << endl;
  cout << a.capacity() << endl;
  a.resize(3);
  print_vector<int>(a);
  a.push_back(23);
  print_vector<int>(a);
  a.reserve_with_allocator(30);
  print_vector<int>(a);
  cout << a.capacity() << endl;

  try {
    throw(a);
  } catch (vector<int> &e) {
    cout << "caught a vector!" << endl;
    print_vector<int>(e);
  }

  // this requires more work to get working
  /* vector<const int> ca{1, 2, 3}; */
  /* cout << ca[1]; */

  return 0;
}
