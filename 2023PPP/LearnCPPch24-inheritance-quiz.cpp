#include <color_macros.h>
#include <iomanip> // setprecision(n), setw
#include <iostream>
#include <string>
#include <typeinfo> // for typeid(foo).name()
#include <vector>

using namespace std;

class Fruit {
private:
  string color_;
  string name_;

public:
  Fruit(string name, string color) : name_{name}, color_{color} {}
  void print() { cout << "My " << name_ << " is " << color_ << "." << endl; }
  virtual void foo() {}
};
class Apple : public Fruit {

private:
  string name_ = "apple";

protected:
  Apple(string name, string color) : Fruit{name + " apple", color} {}

public:
  Apple(string color) : Fruit{"apple", color} {}
  void foo() { cout << "Apple foo" << endl; }
};

class GrannySmith : public Apple {
public:
  GrannySmith(string color) : Apple{"granny smith", color} {}
  void foo() { cout << "Granny foo" << endl; }
};

int main(int argc, char *argv[]) {
  Apple a{"red"};
  GrannySmith g{"green"};

  a.print();
  g.print();

  Fruit *fptr{&a};
  fptr->foo();
  return 0;
}
