
#include <cstdint>
// Hang on a sec... if components are in arrays, you can just use indices.
// eg a Tuple could just consist of 3 indices to 3 component arrays.
// so what would an iterator look like? would you even need one?
// need to register the entity_id and what components it has.
// OMG this is gonna be easy

struct Component {
  // some data
};

// Entity only exists to facilitate querying if needed
struct Entity {
  uint32_t id;
  vector<Component *> components;
};

// Components often used together stored as Archetype
struct DrawArchetype : public Archetype {
  // should this be here? - this could just be the tuple
  // TransformComponent *transform;
  ShapeComponent shape;
  ColorComponent color;
};

// Tuples as a interface to the components a system needs?
// - under the hood they are intelligently packed somehow
struct DrawTuple {
  TransformComponent *transform;
  ShapeComponent *shape;
  ColorComponent *color;
};
// OR have crazy complicated iterators into underlying object pool?

struct DrawSystem : public System {
  void update() {
    for (auto &t : draw_tuples) {
      // draw t.shape at t.transform
    }
  }
};

struct World {
  vector<DrawTuple> draw_tuples;
  vector<DrawArchetype> draw_archetypes vector<TransformComponent> transforms;
};

// in the case of objects like projectiles (can number in 1000's), can add them
// to a separate tuple with 0 pointers

// is this ok? will i still get decent cache hits most likely?
struct FooTuple {
  TransformComponent *transform;
  FooArchetype *arch;
  BarComponent *bar;
};

struct FooSystem : public System {
  void update() {
    for (auto &t : footuples) {
      // draw arch.shape at arch.transform
      // etc
    }
  }
};

struct TextArchetype : public Archetype {
  FontComponent shape;
  ColorComponent color;
};
