#include <cstddef>
#include <list>
class MemoryArena;
struct MemoryArenaPage {
  MemoryArena *arena_;
  char *data;
  size_t size;
  // alignas(alignof(max_align_t)) char data[];
  // max_align_t == 16bytes prob
  MemoryArenaPage(size_t align = sizeof(max_align_t)) {

    // auto alloc_size =
  }
};

class MemoryArena {
private:
  std::list<MemoryArenaPage> pages_;

public:
  size_t page_offset; // position in current page
  size_t total_used;  // full pages
  size_t total_allocated;
};

// learn and implement these
void marena_init(MemArena *arena, size_t min_size);

void marena_deinit(MemArena *arena);

void marena_reset(MemArena *arena);

void *marena_alloc(MemArena *arena, size_t size);

void *marena_alloc_array(MemArena *arena, size_t num_members, size_t size);

void *marena_alloc_aligned(MemArena *arena, size_t size, size_t alignment);
