#include <iostream>
#include <vector>

class Entity {
public:
  int id;
  // has many components, but stored elsewhere contiguously and accessed with id
};
class Component {
public:
  int id;
};

template <typename T> class ObjectPool {
  vector<T> elem; // to access with elem[id]
  // OR
  map<int, T> elem; // to lookup by id

public:
};

int main() {

  ObjectPool<Component> components;

  return 0;
}
