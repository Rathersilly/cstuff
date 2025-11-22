// LearnCPP inheritance chapters are inspo here
//
// Virtual Functions:
// Each class in a hierarchy that contains a virtual function will have a
// hidden *__vtpr that points to a virtual table(vtable), that is a
// static array of the addresses of the most-derived functions
// available to that class.

// not covered here: multiple inheritance, virtual base classes,
// slicing, dynamic_cast, combining friend and virtual functions,
// pointers to members/data members
//
#include <color_macros.h> // for PFUN (prints __PRETTY_FUNCTION__) etc.
#include <iostream>
#include <string>
#include <typeinfo> // for typeid(foo).base_data()
#include <vector>

using namespace std;

class Base {
private:
protected:
  void base_protected_fn() { cout << "base protected" << endl; }

public:
  string base_data_;
  int some_public_variable; // to make private with "using" in Derived

  Base() { PFUN; }
  Base(string base_data) : base_data_{base_data} { PFUN; }

  // make destructors virtual if derived class might have to
  // deallocate resources.
  // but remember: a class with virtual function(s) in it's hierarchy
  // has slight vtable overhead
  virtual ~Base() {}

  void function_to_delete(); // = delete in Derived to delete

  void print() { cout << "Base print" << endl; }

  // Virtual Functions:
  // virtual function will call derived version, even from ptr to Base
  // note - if a function is declared virtual, that function
  // in all derived classes is implicitly virtual
  virtual void virtual_function_demo() { PFUN; }

  // pure virtual function is never meant to be called - only overridden
  // but a class with a pure virtual function becomes
  // an "abstract class," and can never be instantiated!
  /* virtual void pure_virtual_function() = 0; */

  // Covariant Return Types 1/2:
  // This version of getThis() returns a pointer to a Base class
  virtual Base *getThis() {
    std::cout << "called Base::getThis()\n";
    return this;
  }

  friend ostream &operator<<(ostream &, const Base &);
};

// :public Base means public members in Base remain public
// :private Base would mean public members become private
// :protected Base would mean public members become protected
// final means virtual lookups stop at this class
class Derived final : public Base {
private:
  // https://stackoverflow.com/questions/180601/using-super-in-c
  typedef Base super; // can use super::super::somefunc without knowing names
  typedef Base inherited; // common alternative to super

  using Base::some_public_variable; // change access of member to private
  string derived_data_;

public:
  // using gives public access to a protected fn
  // (can't do this for private fn, because subclass doesnt have access)
  using Base::base_protected_fn;

  Derived(){PFUN} // this will call Base() then Derived()
  /* Derived() = default; // this will ONLY call Base() */

  // Subclass constructors will call superclass constructors, but we can
  // determine which superclass ctor is called.
  Derived(string base_data, string derived_data)
      : Base{base_data}, derived_data_{derived_data} {
    PFUN
  }

  void function_to_delete() = delete; // delete a function in subclass

  void print() {
    super::print();
    cout << "Derived print" << endl;
  }

  // override tells both programmer and compiler of intention - for
  // info/debugging only.
  // final means virtual lookups end with this class/function
  void virtual_function_demo() final override { PFUN; }

  virtual void pure_virtual_function() { PFUN; }

  // Covariant Return Types 2/2:
  // Normally override functions have to return objects of the same type as the
  // base function However, because Derived is derived from Base, it's okay to
  // return Derived* instead of Base*
  Derived *getThis() override {
    std::cout << "called Derived::getThis()\n";
    return this;
  }

  friend ostream &operator<<(ostream &, const Derived &);
};

ostream &operator<<(ostream &os, const Base &base) {
  return os << "base_data: " << base.base_data_ << endl;
}
ostream &operator<<(ostream &os, const Derived &der) {
  // to call the base_class version from friend function
  os << static_cast<const Base &>(der);

  return os << "derived_data: " << der.derived_data_ << endl;
}

int main(int argc, char *argv[]) {
  Base bfoo("hello");
  Derived dbar("whats up", "dude");

  // demos calling base function from derived function
  cout << bfoo; // calls base function
  cout << dbar; // calls base function from derived function
  dbar.print();

  // demo calling protected function that was made public in Derived
  dbar.base_protected_fn();

  // virtual function demo - calling Derived function from a Base ptr
  Base *base_ptr{&dbar};
  base_ptr->virtual_function_demo();
  // explicitly calling Base's version of virtual function
  base_ptr->Base::virtual_function_demo();

  dbar.pure_virtual_function();
  return 0;
}
