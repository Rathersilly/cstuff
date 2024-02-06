// HOF - vector emplace_back() - with some smart pointers
//
// template< class... Args >
// constexpr reference emplace_back(Args &&...args); (since C++ 20)
//
// emplace_back(), like push back(), appends (allocates space if needed)
//    but constructs object in place.
//    Object is owned by vector.
//
// Ownership determines:
//    Object Lifetime - where an object is in scope
//    Deallocation    - owner is responsible for deallocating objects memory
//
// Ownership is created by:
//    emplace_back()  - as discussed
//    smart pointers  - unique_ptr, shared_ptr
//
// Ownership is NOT created by:
//    raw pointers    - object created with new will outlive a raw pointer

#include <iostream>
#include <memory> // std::unique_ptr
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

void emplace_demo() {
  // OK - object is owned by base_vector and is destructed when base_vector goes
  //     out of scope
  base_vector.emplace_back(); // OK - Constructs a Base object

  // GOOD - object is owned by base_uniq_ptr_vector
  base_uniq_ptr_vector.emplace_back(
      make_unique<Base>()); // OK - Constructs a Base object
  base_uniq_ptr_vector.emplace_back(
      make_unique<Derived>(42)); // OK - Constructs a Derived object

  // Alternative to emplace_back()
  std::unique_ptr<Base> bar = std::make_unique<Derived>();
  base_uniq_ptr_vector.push_back(std::move(bar)); // OK
  // This uses unique_ptr's move() - NOT bar's move ctor(if it has one)
  //
  // DO NOT access bar now - it is in a valid but unspecified state.
  // - access it through the unique_ptr

  // base_uniq_ptr_vector.push_back(bar);         // Not OK - compile error

  // base_uniq_ptr_vector.emplace_back(new Base); // Not OK - Cannot implicitly
  //     convert *Base to unique_ptr<Base>

  // Not OK - compile error: use of deleted function
  // std::unique_ptr<Base> baz = std::make_unique<Derived>();
  // base_uniq_ptr_vector.push_back(baz);

  // DANGER! - when vector goes out of scope, so do its pointers, but the
  //      objects are NOT destroyed
  // - Requires a dedicated cleanup fn or a custom vector with destructor that
  //      deletes its objects
  // - Slightly less overhead than unique_ptr but its NBD
  base_ptr_vector.emplace_back(new Base); // OK - Constructs a Base object
  base_ptr_vector.emplace_back(
      new Derived(42)); // OK - Constructs a Derived object
}

int main(int argc, char *argv[]) {

  emplace_demo();
  // Accessing the gooey center of base_uniq_ptr_vector
  for (auto a = base_uniq_ptr_vector.begin(); a != base_uniq_ptr_vector.end();
       ++a) {
    cout << a->get()->id << endl;
  }
  return 0;
}
