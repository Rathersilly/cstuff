// Simple implementation of Godot-like RefCounted class
// and Ref<T> (like std::shared_ptr)

// Invasive/Intrusive counting
//
// std::shared_ptr uses non-invasive reference counting:
// it stores ref_count in a control block.
//
// inheriting a RefCounted class uses invasive counting:
// storing ref_count in the RefCounted class is better for locality,
// as well as integration with custom memory allocators and custom thread safety
//
// Ref<T> is like shared_ptr<T>, except stores count in the RefCount class

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <vector>

using namespace std;
using namespace fmt;

struct RefCounted {
  inline static int class_id = 0;
  int id;
  // this needs be atomic in actual version
  // as well as adding thread safety elsewhere
  int ref_count = 0;

  inline static vector<RefCounted *> things;
  RefCounted() : id{class_id++} { things.push_back(this); }

  void reference() { ++ref_count; }
  void unreference() {
    if (ref_count == 1)
      delete this;
    else
      --ref_count;
  }
};

template <typename T> struct Ref {
  T *ptr = nullptr;

  Ref(T *p) : ptr{p} {
    if (ptr)
      ptr->reference();
  }
  Ref(Ref<T> &other) {
    ptr = other.ptr;
    ptr->reference();
  }

  // copy assignment - returns void rather than *this in order to prevent
  // chaining (a = b = c) and encourage explicit use
  void operator=(const Ref &other) {
    if (other.ptr) {
      other.ptr->reference();
    }
  }

  ~Ref() {

    if (ptr)
      ptr->unreference();
  }
  T operator*() { return ptr; }
  T *operator->() { return ptr; }
};

struct Foo : public RefCounted {
  int a;
};

int main(int argc, char *argv[]) {
  Ref<Foo> f = new Foo;
  // print("{} \n", f1.id);
  // print("{} \n", f2.id);
  // print("{} \n", f3.id);
  // auto f4 = Ref<Foo>{&f3};
  // print("{} \n", f4->id);
  auto f5 = Ref<Foo>{f};
  //
  Ref<Foo> f6 = f;
  return 0;
}
