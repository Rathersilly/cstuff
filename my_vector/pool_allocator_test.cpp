// TODO: create my_pool_allocator.h
// figure out how memory pools work first
// could have array of bools with open spaces and allocate to first open space
// or attempt to keep things contiguous by cache line

// eg when asked for n bytes, see if theres a line with n free bytes
// else start a new line
// perhaps have a function to defrag
#include "my_vector.h"
#include <algorithm>
#include <cassert>
#include <color_macros.h>
#include <iostream>
#include <vector>

// Test allocator to memory pool
template <class T> class PoolAllocator {
private:
  void *mPool;
  size_t mSize;

public:
  void allocate(size_t n) {}
  void deallocate(size_t n) {}
  PoolAllocator(void *pool, size_t bytes) {}
};

void *gMemoryPool;
int main(int argc, char *argv[]) {
  gMemoryPool = malloc(256);
  PoolAllocator<int> allocator(gMemoryPool, 256);
  return 0;
}
