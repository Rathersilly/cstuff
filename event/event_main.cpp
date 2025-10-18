#include "events.h"
// #include "events_with_observer_class.h"

// HOW SDL3 event system works:
// in events.c:
// there is a static struct SDL_EventQ - private to that file
// SDL_EventQ has a linked list of SDL_EventEntry and a free list (object pool)
// - SDL_Event
// - SDL_EventEntry is node containing SDL_Event and prev/next ptrs
// - popped EventEntries are added to free list for reuse
// - array is not as necessary as one might think - small N,
// - events are popped, not traversed
// - if you have time, array vs list wouldbe worth testing.

using Tick = uint_fast64_t;

array<Entity, 10> gEnts;
EventSystem gEvents; // could be singleton or part of Game/GameManager

// One output provided by SDL is the eventqueue
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
