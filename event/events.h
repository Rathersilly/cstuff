#pragma once
// Implementation of Observer Pattern for an Event Queue
//
// TODO: maybe the scancode should be the subject, not the event system
// also remove observers - also test
// maybe subject gives "dying breath" in destructor
// maybe observer removes itself in destructor
//
// in the case of logging/profiling could just have a function rather
// than inherit observed.
// that function could then pass on to whatever else, and use
//
// TODO: Implement Logging - that could actually use Observer classes
// // Alternate implementation - having obbservation properties be inherited
// // - Doesnt really work here
// // - the Subject(KeyCode) is not the notifier, the System is
// // - This causes some extra coupling but is justified here for O() reasons
//
// class Observer {
//   virtual on_notify(event){}
// };
// class ObserverSubject {
// public:
//   vector<Observer *> observers;
//
// protected:
//   virtual void notify();
//   // entity id
//   // data?
// };
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
inline std::mt19937 mt{std::random_device{}()};

using Tick = uint_fast64_t;
using Code = uint_fast64_t;
using ID = int_fast64_t;

// temporary - will be unneeded when systems are member of Game
// Entity is Observer of a code (from an event). It is notified by EventSystem
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

// Mock Object that generates events for the queue that EventSystem will handle
// in practice this will be done by by SDL with API like SDL_PollEvent
class EventGenerator {
public:
  // only creating KeyboardEvent atm
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
    int events_to_create = 3;
    for (int i = 0; i < mt() % events_to_create; ++i) {

      queue.emplace_back(create_random_event());
    }
  }
};

// KeyObservers contains the observers of a particular event code
// - the Observers are notified by the EventSystem
struct KeyObservers {

  Code code;
  vector<ID> observers;
};

// EventObservatory keeps track of all observers of all keys.
// - EventSystem loops through this so we only have to
// - iterate through events that something cares about
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

// EventSystem distributes events to the components that observe that event
class EventSystem {

  // EventSystem has 2 inputs:
  // - event queue (dependency injected) (maybe better aggregated)
  // - Observatory (contains observed events + their observers)

  // EventSystem has 1 output:
  // - needs access to the main entity list (in Game or Global)
  EventObservatory observatory;

public:
  array<Entity, 10> *ents;

  // could put this in Observatory - reduce coupling
  // - OR have all event interaction go through the System - uniform interface
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
      // loop container of interesting scancodes in EventObservatory
      // notify observers of that scancode
      for (auto &entry : observatory.entries) {
        // TODO: make Event inheritance work
        if (e.code == entry.code)
          cout << "code is observed" << endl;
        for (auto obs : entry.observers) {
          // how to send notification with just an ID
          // game has an EventSystem and a list of Entities
          // obs.notify(code) - notify observers of that code
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
