
#include <iostream>
#include <string>
using namespace std;

// scoped enum
// access with scope resolution operator ::
enum class TypeofThing { cat, lawyer };
TypeofThing foo = TypeofThing::cat;

// unscoped enum
// can crowd the namespace
enum { cat, lawyer };
auto goo = cat;

// classes for Tagged Union demo
struct Cat {
  TypeofThing type;
};
struct Lawyer {
  TypeofThing type;
};

// example of enums and unions in SDL3
typedef enum SDL_EventType {  // This is a scoped enumeration
  SDL_EVENT_FIRST = 0,        // enums start at 0
  SDL_EVENT_KEY_DOWN = 0x300, // can specify new starting point
  SDL_EVENT_KEY_UP,           // will be 0x301
} SDL_EventType;

typedef struct SDL_KeyboardEvent {
  SDL_EventType type; /**< SDL_EVENT_KEY_DOWN or SDL_EVENT_KEY_UP */
  // SDL_Scancode scancode; /**< SDL physical key code */
  // SDL_Keycode key;       /**< SDL virtual key code */
  // SDL_Keymod mod;        /**< current key modifiers */

  bool down;   /**< true if the key is pressed */
  bool repeat; /**< true if this is a key repeat */
} SDL_KeyboardEvent;

// union Event {
//   Uint32 type; /**< Event type, shared with all events, Uint32 to cover user
//                   events which are not in the SDL_EventType enumeration */
//   SDL_CommonEvent common;          /**< Common event data */
//   SDL_DisplayEvent display;        /**< Display event data */
//   SDL_WindowEvent window;          /**< Window event data */
//   SDL_KeyboardDeviceEvent kdevice; /**< Keyboard device change event data */
//   SDL_KeyboardEvent key;           /**< Keyboard event data */
// };

int main() {

  // union will have a (minimum) size = to size of largest member
  union Number { // this union has size 4 (short is 2, int is 4)
    short s;
    int i;
  } num; // this is same as having Number num; on the next line

  // assigning to non-first union member will overwrite earlier members
  num.i = 0xaabbccdd;
  std::cout << hex << "short is: " << num.s << '\n' // ccdd
            << "int is: " << num.i << '\n';         // aabbccdd

  // assigning to the smaller first member will then overwrite later members
  num.s = 0x22;
  std::cout << hex << "short is: " << num.s << '\n' // 0022
            << "int is: " << num.i << '\n';         // aabb0022

  // Accessing an "unfocused member" may lead to undefined behavior
  //    BUT
  // a Tagged Union is a C pattern that takes advantage of this
  // if the first union member is also the first member of a member:
  union Thing {
    TypeofThing type; // enum is good for this
    Cat cat;          // these structs have a TypeofThing type first member
    Lawyer lawyer;
  };

  Thing thing;
  thing.lawyer.type = TypeofThing::lawyer;
  cout << (int)thing.lawyer.type << endl;
  // since type is the first member, can access thing.lawyer.type like this:

  cout << (int)thing.type << endl;
  thing.cat.type = TypeofThing::cat;
  cout << (int)thing.cat.type << endl;
  cout << (int)thing.type << endl;

  // this will be undefined behavior - a lawyer is not a cat!
  cout << (int)thing.lawyer.type << endl;
  cout << (int)thing.type << endl;

  // Tagged Unions are like manual polymorphism
  // can use a switch to
  // discriminate future action
  // eg switch(event.type)
  // case SDL_EVENT_KEY_DOWN

  // unions can be anonymous
  union {
    short a;
    int i;
  };
  i = 0xaabbccdd;
  cout << i << endl;

  // a class may include an anonymous union - may be tagged
  struct Foo {

    enum { CHAR, INT } tag;
    union {
      char c;
      int a;
    };
  };
  Foo f{Foo::INT, 'c'};
}
