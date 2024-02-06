// HOF TODO
// list and demo the most comming std::vector methods
//

#include <iostream>
#include <memory>
#include <vector>
#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
using namespace std;

class Base {
public:
  inline static int count = 0;
  int id;
  Base() {
    cout << "Constructing Base" << endl;
    id = count;
    ++count;
  }
  virtual ~Base() { cout << "Destructing Base" << endl; }
};

class Derived : public Base {
public:
  Derived() { cout << "Constructing Derived" << endl; }
  Derived(int x) { cout << "Constructing Derived with int: " << x << endl; }
  ~Derived() override { cout << "Destructing Derived" << endl; }
};

vector<Derived> derived_vector;
vector<Base> base_vector;
vector<Base *> base_ptr_vector;
vector<std::unique_ptr<Base>> base_uniq_ptr_vector;

int main(int argc, char *argv[]) { return 0; }
