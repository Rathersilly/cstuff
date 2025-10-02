#include <string>
using namespace std;

template <class T>
concept CanSpeak =
    requires(T a) {
      a->has_base
    }

class Animal {
  string name;
  void speak() { cout << "???" << endl; }
};
template <CanSpeak T>
void make_speak() template <Animal a>
class Cat : public Animal {
  void speak() { cout << "Meow" << endl; }

} int main(int argc, char *argv[]) {

  int a;
  return 0;
}
