// #include "events.h"
#include "events_with_observer_class.h"

// ok basic random events created and handled.. now what was the point of this
//

using Tick = uint_fast64_t;

array<Entity, 10> gEnts;
EventSystem gEvents; // could be singleton or part of Game/GameManager
std::deque<KeyboardEvent> gEventQueue;

int main(int argc, char *argv[]) {
  gEvents.ents = &gEnts;
  gEnts[0] = Entity{0};
  gEnts[1] = Entity{1};
  gEvents.add_observer(0, 0);
  gEvents.print_observers();
  gEvents.add_observer(0, 1);
  gEvents.print_observers();
  gEvents.add_observer(1, 1);
  gEvents.print_observers();

  while (true) {

    gEvents.handle_events(gEventQueue);
    std::this_thread::sleep_for(100ms);
    EventGenerator::add_events(gEventQueue);
    cerr << "queue size: " << gEventQueue.size()
         << " front: " << gEventQueue.front().type << endl;
    // gEvents.print_events(gEventQueue);
  }

  return 0;
}
