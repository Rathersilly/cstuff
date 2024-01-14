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
    return *(vstr.end() - 1);
  }
}

// TODO this would be a great thing to constrain with concept/requirement
// not sure why this template doesnt work but the explicit version
// says "could not deduce template parameter A
/* template <class A, class B> */
/* std::vector<A> list_to_vector(const std::list<B> &lst) { */
std::vector<double> list_to_vector(const std::list<int> &lst) {
  std::vector<double> vec;
  /* std::vector<A> vec; */
  for (auto a : lst) {
    /* for (auto a = lst.begin(); a != lst.end(); ++a) { */
    vec.push_back(a);
  }
  return vec;
}

// this version works fine, but probably better off returning void and changing
// args
template <class A, class B>
std::vector<B> list_to_vector2(const std::list<A> &lst, std::vector<B> &vec) {
  for (auto a : lst) {
    /* for (auto a = lst.begin(); a != lst.end(); ++a) { */
    vec.push_back(a);
  }
  return vec;
}
// error: no matching function call
// gives this function as candidate, but template argument deduction failed
// couldn't deduce parameter B
// i guess the return value in the function is not enough to go on
template <class A, class B>
std::vector<B> list_to_vector3(const std::list<A> &lst) {
  std::vector<B> vec;
  for (auto a : lst) {
    /* for (auto a = lst.begin(); a != lst.end(); ++a) { */
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

// this works fine
template <class A> std::vector<double> foo(const std::list<A> &lst) {
  std::vector<double> v;
  return v;
}
// error "couldnt deduce template parameter A"
template <class A> std::vector<A> bar(const std::list<int> &lst) {
  std::vector<A> v;
  return v;
}
// error "non-class, non-variable partial specialization 'baz<A>' is not allowed
/* template <class A> std::vector<A> baz<A>(const std::list<int> &lst) { */
/*   std::vector<A> v; */
/*   return v; */
/* } */

// why does this work fine, however
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
  std::vector<double> vdouble = list_to_vector(lint);
  print_vector(vdouble);
  cout << compare_list_vector(lint, vdouble);
  vdouble.push_back(3);
  cout << compare_list_vector(lint, vdouble);
  std::vector<double> vdouble2;
  vdouble2 = list_to_vector2(lint, vdouble2);
  cout << "222" << endl;
  print_vector(vdouble2);

  std::vector<double> vdouble3;
  vdouble3 = list_to_vector3(lint);
  print_vector(vdouble3);

  /* vdouble = asdf(lint); */
  /* vdouble = foo(lint); */
  /* vdouble = bar(lint); */
  /* vdouble = baz<double>(lint); */

  my::vector<int> v = {1, 2, 3, 4, 5};
  std::cout << v;
  v << 6;
  std::cout << v;

  return 0;
}
