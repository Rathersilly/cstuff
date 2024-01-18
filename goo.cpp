#include <color_macros.h>

#include <initializer_list>
#include <queue>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
/* using std::string; */
/* using std::stringstream; */

using namespace std;
class Dog {};
template <class T> class myvector {
  T *elem;

public:
  myvector(std::initializer_list<T> lst) {
    /* for(auto a = lst.begin */
    elem = new T[lst.size()];
    int i = 0;
    for (auto a : lst) {
      elem[i] = *a;
      ++i;
    }
  }
};

template <class T> void meow(T t) { cout << "meow"; }

int main(int argc, char *argv[]) {
  // dont have to specify meow<int> - template arg deduction
  meow(2);
  // these aren't deduced, however, even without the (ints)
  /* vector<int> v{(int)1, (int)2, (int)3}; */
  /* vector<int> v2{1, 2, 3}; */
  /* Dog a; */
  /* myvector myv{a}; */

  return 0;
}
