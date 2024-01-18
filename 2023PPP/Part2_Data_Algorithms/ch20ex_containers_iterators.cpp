// Ch 20 exercises - only finished a few but this file has examples of
// attempting to use template for return value -
// we see what works and what doesnt

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>
/* #include <vector> */
#include "my_vector.h"
using namespace my;
using namespace std;

template <typename T> void print_vector(const std::vector<T> &v) {
  for (auto i = 0; i < v.size(); ++i) {
    std::cout << v[i] << " ";
  }
  std::cout << endl;
}

// Ex 5 - define >> and << for vector
// << is push_back() or used to print to an ostream
// not sure what they want >> to do
template <typename T>
ostream &operator<<(ostream &os, const my::vector<T> &vec) {

  for (auto i = vec.begin(); i != vec.end(); ++i) {
    os << *i << " ";
  }
  os << endl;
  return os;
}

string find_last_word(string str) {
  std::vector<string> vstr{};
  stringstream vsstream(str);
  string word;
  while (getline(vsstream, word, ' ')) {
    vstr.push_back(word);
  }
  if (vstr.size() == 0) {
    return ""s;
  } else if (vstr.size() == 1) {
    return vstr[0];
  } else {
    sort(vstr.begin(), vstr.end());
    /* print_vector(vstr); */
    return *(vstr.end() - 1);
  }
}

// TODO maybe concept/require something here
//
// you pass template params from <> in function call, if they cant be deduced
// you dont need <> in the function definition, except where they replace
// what would normally be a type
// the static_cast is not necessary since we were explicit in the call.
template <class A, class B>
std::vector<B> list_to_vector(const std::list<A> &lst) {
  std::vector<B> vec;
  /* for (auto a : lst) { */
  for (auto a = lst.begin(); a != lst.end(); ++a) {
    /* vec.push_back(static_cast<B>(*a)); */
    vec.push_back(*a);
  }
  return vec;
}
// this version works fine, but probably better off returning void and changing
// args
template <class A, class B>
std::vector<B> list_to_vector2(const std::list<A> &lst, std::vector<B> &vec) {
  for (auto a : lst) {
    vec.push_back(a);
  }
  return vec;
}

// simplified version of the above, for testing purposes (still doesnt work)
// error "could not deduce template parameter A
template <class A, class B> std::vector<B> asdf(const std::list<A> &lst) {
  std::vector<double> vec;
  return vec;
}

template <class A, class B>
bool compare_list_vector(const std::list<A> &lst, const std::vector<B> &vec) {
  if (lst.size() != vec.size())
    return false;

  auto vit = vec.begin();
  for (auto lit = lst.begin(); lit != lst.end(); ++lit) {
    if (*lit != *vit)
      return false;
    ++vit;
  }
  return true;
}

int main(int argc, char *argv[]) {

  // Ex 7 - find lexicographical last string in usorted vector<string>
  string str = "why hello there whats up?";
  cout << "last word of \"" << str << "\" is \"" << find_last_word(str) << "\""
       << endl;

  // Ex 11 - copy list<int> into vector<double> and verify
  std::list<int> lint{1, 2, 3, 4, 5, 99, 100};
  std::vector<double> vdouble = list_to_vector<int, double>(lint);
  vdouble = list_to_vector<int, double>(lint);
  print_vector(vdouble);
  cout << compare_list_vector(lint, vdouble);
  vdouble.push_back(3);
  cout << compare_list_vector(lint, vdouble);
  std::vector<double> vdouble2;
  vdouble2 = list_to_vector2(lint, vdouble2);
  cout << "---" << endl;
  print_vector(vdouble2);

  my::vector<int> v = {1, 2, 3, 4, 5};
  std::cout << v;
  v << 6;
  std::cout << v;

  return 0;
}
