#include <vector>
using namespace std;

struct Component {};
struct PositionComponent {};
struct TextureComponent {};
struct Entity {};
struct System {
  virtual void update();
};
struct DrawSystem : System {
  vector<Component *> reqs{PositionComponent, TextureComponent};
  Component
      // needs to see certain components (tuple?)
      void
      update() override {
    // using the components that this system requires
    // do what must be done
    ;
    ;
  }
};
struct World {
  vector<System *> systems;
  void update() {
    for (auto s : systems) {
      s->update();
    }
  }
};
int main(int argc, char *argv[]) {
  World world;
  DrawSystem *ds;
  world.systems.push_back(ds);
  world.update();

  return 0;
}
