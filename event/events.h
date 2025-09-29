#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <color_macros.h>
#include <cstdint>
#include <deque>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <variant>
#include <vector>
using namespace std;
using namespace std::chrono_literals;
using namespace std::chrono;
std::mt19937 mt{std::random_device{}()};

using Tick = uint_fast64_t;
using Code = uint_fast64_t;
using ID = int_fast64_t;
// temporary - will be unneeded when systems are member of Game
struct Entity {
  ID id;
  void notify(Code code) {
    cout << "Entity " << id << " notified of code " << code << endl;
    std::this_thread::sleep_for(100ms);
  }
};

struct KeyboardEvent {
  Tick timestamp;
  string type = "KeyboardEvent"s;
  Code code;
  KeyboardEvent() {}
  KeyboardEvent(Code c, string t = "KeyboardEvent"s) : code{c}, type{t} {}
};
// struct MouseEvent {
//   Tick timestamp;
//   string type;
//   std::pair<int, int> pos;
//   bool button1 = false;
//   bool button2 = false;
//   MouseEvent() {}
//   MouseEvent(string t = "MouseEvent"s) : type{t} {}
// };
//
// struct WindowEvent {
//   Tick timestamp;
//   string type;
//   WindowEvent() {}
//   WindowEvent(string t = "WindowEvent"s) : type{t} {}
// };
// using Event = std::variant<KeyboardEvent, MouseEvent, WindowEvent>;

class EventGenerator {
public:
  static KeyboardEvent create_random_event() {

    auto e = KeyboardEvent{static_cast<Code>(mt() % 2)};
    cout << "creating KeyboardEvent w/ code = " << e.code << endl;
    return e;
    TRACE_GREEN();
    switch (mt() % 3) {
    case 0:
      return KeyboardEvent{static_cast<Code>(mt() % 2)};
      break;
    case 1:
      // return MouseEvent{};
      break;
    case 2:
      // return WindowEvent{};
      break;
    }
    return KeyboardEvent{0};
  }

  static void add_events(std::deque<KeyboardEvent> &queue) {
    TRACE_BLUE();
    for (int i = 0; i < mt() % 3; ++i) {

      queue.emplace_back(create_random_event());
    }
  }
};

class Observer {
  // virtual on_notify(event){}
};
class Observed {
protected:
  virtual void notify();
  // entity id
  // data?
};

struct KeyObservers {
  Code code;
  vector<ID> observers;
};

struct EventObservatory {
  vector<KeyObservers> entries;

  void push_back(Code code, ID id) {
    // find entry with code == code
    for (auto &entry : entries) {
      // code is being observed by something
      if (entry.code == code) {

        // code is NOT already observed by this id
        if (find(entry.observers.begin(), entry.observers.end(), id) ==
            entry.observers.end()) {
          entry.observers.push_back(id);
          return;
        }
        return; // code is already observed by this id
      }
    }
    // cout << "new observer code: " << code << " id: " << id << endl;
    auto new_entry = KeyObservers{code};
    new_entry.observers.push_back(id);
    // cout << "new entry code: " << new_entry.code
    //      << " id: " << new_entry.observers.back() << endl;
    entries.push_back(new_entry);
  }
};

class EventSystem {
  // is OBSERVED SUBJECT of observer pattern
  // is OBSERVED BY OBSERVERS (eg input_component)

  // each interesting code has a list of observers
  EventObservatory observatory;

public:
  array<Entity, 10> *ents;
  void add_observer(Code code, ID obs) { observatory.push_back(code, obs); }
  void print_observers() {
    TRACE_GREEN();
    for (auto &entry : observatory.entries) {
      cout << "code: " << entry.code << " observer ids: ";
      for (auto &id : entry.observers)
        cout << id << " ";
      cout << endl;
    }
    cout << endl;
  }

  void handle_events(std::deque<KeyboardEvent> &queue) {
    KeyboardEvent e;
    while (poll_event(&e, queue)) {
      cout << "handling event:" << e.type << endl;
      // loop container of interesting scancodes
      // notify observers of that scancode
      // but want to limit O(n)
      for (auto &entry : observatory.entries) {
        // TODO: make Event inheritance work
        if (e.code == entry.code)
          cout << "code is observed" << endl;
        for (auto obs : entry.observers) {
          // how to send notification with just an ID
          // the game has an EventSystem
          // and also a list of Entities
          // obs.notify(code);
          // notify observers of that code
          cout << " should notify entity: " << obs << endl;
          (*ents)[obs].notify(entry.code);
        }
      }
    }
  }

  bool poll_event(KeyboardEvent *e, std::deque<KeyboardEvent> &queue) {
    if (queue.empty())
      return false;
    e = &queue.front();
    queue.pop_front();
    return true;
  }

  void print_events(const std::deque<KeyboardEvent> &queue) {

    TRACE_YELLOW();
    for (auto &e : queue) {
      cout << e.type << " ";
    }
    cout << endl;
  }
};
