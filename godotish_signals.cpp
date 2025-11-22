// simple implementation of Godot-like signals with callbacks
// tag observer pattern
//
// TODO: create this functionality:
// player.hit.connect(_on_player_hit.bind("sword", 100))
// 	- will need the signal to be an object with a connect function
#include <any>
#include <functional>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

// struct Signal {
//   enum Type { qwer, asdf };
//   Type type;
// };
// Signal is not needed, it can just be a string
enum class Signal { qwer, asdf, zxcv };
using Callback = std::function<void()>;
class Object;

// consider any with any_cast to have callbacks with different signatures
// using Callback = std::any;

// since observer, signal, and callback are linked logically, struct seems good
struct Connection {
  Object *observer;
  Signal signal;
  Callback fun;
};

// or alternatively to Connection,
// struct Subscriber {
//   Object *watcher;
//   Callback fun;
// };
//
// and then in Object, have container:
// std::unordered_map<Signal, std::list<Subscriber>> signal_subscribers;
// or we can make signal be a string:
// std::unordered_map<std::string, std::list<Subscriber>> signal_subscribers;

class Object {

public:
  std::list<Connection> connections;
  void emit(const Signal &signal) {
    for (auto &conn : connections) {
      if (conn.signal == signal) {
        conn.fun();
      }
    }
  };

  void connect_to(Object &other, Signal signal, Callback fun) {
    other.connections.emplace_back(&other, signal, std::move(fun));
  }

  static void print_int(int num) {
    cout << num << "\t\t" << __PRETTY_FUNCTION__ << endl;
  }
  void say_hi() { cout << "hi from " << __PRETTY_FUNCTION__ << endl; }
  static void some_static_function() {
    cout << "hi from " << __PRETTY_FUNCTION__ << endl;
  }
};

int main(int argc, char *argv[]) {
  Object foo;
  Object bar;
  auto fun = [] {
    cout << "hi" << endl;
    return;
  };
  Signal qwer{Signal::qwer};
  Signal asdf{Signal::asdf};
  Signal zxcv{Signal::zxcv};
  bar.connect_to(foo, qwer, fun);
  foo.emit(qwer);

  bar.connect_to(foo, asdf, Object::some_static_function);
  foo.emit(asdf);

  // to use Class member function as a callback:
  // 1. Lambda
  auto lambda_member_callback = [&foo]() { foo.say_hi(); };

  // 2. std::bind
  // class member functions have an implicit "this" as first argument
  // eg compiler translates bar.say_hi() to say_hi(&bar)
  Callback bound_member_callback = std::bind(&Object::say_hi, &bar);

  bar.connect_to(foo, zxcv, bound_member_callback);
  bar.connect_to(foo, zxcv, lambda_member_callback);
  bar.connect_to(foo, zxcv, std::bind(Object::print_int, 2));

  foo.emit(zxcv);
  return 0;
}
