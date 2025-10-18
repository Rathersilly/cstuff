// HOW SDL3 event system works:
// in events.c:
// there is a static struct SDL_EventQ - private to that file
// events are added/removed through the interface
// SDL_EventQ is a pooled linked list of SDL_EventEntry
//
// - SDL_EventEntry is node containing SDL_Event and prev/next ptrs
// - popped EventEntries are added to free list for reuse
// - array is not as necessary as one might think:
// - small N, events are popped, not traversed
// - if you have time, array vs list wouldbe worth testing.

// - SDL_TemporaryMemory is another pooled linked list for misc purposes (idk)
typedef struct SDL_TemporaryMemory {
  void *memory;
  struct SDL_TemporaryMemory *prev;
  struct SDL_TemporaryMemory *next;
} SDL_TemporaryMemory;

typedef struct SDL_EventEntry {
  SDL_Event event;
  SDL_TemporaryMemory *memory; // mostly unused - break glass...
  struct SDL_EventEntry *prev;
  struct SDL_EventEntry *next;
} SDL_EventEntry;

static struct {
  SDL_Mutex *lock; // locks when adding/removing events
  bool active;     // inactive = back in pool
  SDL_AtomicInt count;
  int max_events_seen;
  SDL_EventEntry *head;
  SDL_EventEntry *tail;
  SDL_EventEntry *free; // first free allocated SDL_EventEntry
} SDL_EventQ = {NULL, false, {0}, 0, NULL, NULL, NULL};
