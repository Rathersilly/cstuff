#include <iostream>
#include <sstream>

#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
#define INFO cout << "\t" << __PRETTY_FUNCTION__ << endl;
using namespace std;

// Ex 1 - strdup
char *strdup(const char *c) {
  if (!*c) {
    return nullptr;
  }
  int len = 0;
  while (*(c + len)) {
    len += 1;
  }
  char *res = new char[len + 1];
  for (int i = 0; i < len; ++i) {
    *(res + i) = *(c + i);
  }
  return res;
}
// Ex 2 - findx
char *findx(const char *s, const char *x) {

  int i = 0;
  /* char *res = nullptr; */
  bool match = false;
  int i_memo = 0;
  while (*(s + i)) {
    int j = 0;
    i_memo = i;
    while (*(x + j)) {
      if (*(s + i + j) == *(x + j)) {
        match = true;
      } else {
        match = false;
        break;
      }
      ++j;
    }
    if (match == true) {
      return const_cast<char *>(s) + i;
    }
    i = i_memo + 1;
  }

  return nullptr;
}

// Ex 3 - strcmp

// Ex 4 - if you give the preceding 3 functions a non-cstring, they will read
// past the end of the string - undefined behavior and segfault

// Ex 5-7 - concatenate strings with a separator in the middle
// careful with the char* version of cat_dot -
// its super easy to forget to delete the allocated mem.
string cat_dot(const string &s1, const string &s2, const string &sep = ".") {
  INFO stringstream ss;
  ss << s1 << sep << s2;
  return ss.str();
}
char *cat_dot(const char *s1, const char *s2, const char *sep = ".") {
  INFO int i = 0;
  const char *iter = s1;

  // finding length of return string
  while (*iter) {
    i++;
    iter++;
  }
  iter = s2;
  while (*iter) {
    i++;
    iter++;
  }
  iter = sep;
  while (*iter) {
    i++;
    iter++;
  }
  // creating return string
  char *memo = new char[i];
  iter = s1;
  i = 0;
  while (*iter) {
    *(memo + i) = *iter;
    ++i;
    ++iter;
  }
  iter = sep;
  while (*iter) {
    *(memo + i) = *iter;
    ++i;
    ++iter;
  }
  iter = s2;
  while (*iter) {
    *(memo + i) = *iter;
    ++i;
    ++iter;
  }

  return memo;
}

void print(char *str) {
  if (!str || !*str) {
    cout << endl;
    return;
  }
  for (int i = 0; *(str + i); ++i) {
    cout << *(str + i);
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
  char c[] = "hello";
  char *d = strdup(c);
  print(d);

  // testing findx
  char str[] = "hwelwolo world";
  char x[] = "wor";
  cout << "test findx: ";
  char *pos = findx(str, x);
  print(pos);
  char y[] = "123";
  cout << "test findx: ";
  char *pos2 = findx(str, y);
  print(pos2);

  string s1 = "hi";
  string s2 = "there";
  cout << cat_dot(s1, s2) << endl;
  cout << cat_dot("sup", "dog", "my") << endl;

  return 0;
}
