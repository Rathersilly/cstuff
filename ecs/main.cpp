// TODO: find a way to have system know what it is looking for
// each entity has certain components
// each system requires certain components
// at compile time, create a structure that has a list of all entities that each
// system can effect?
// but what about adding entities at run time?
#include <cstdlib>
#include <unordered_map>
#include <vector>

using namespace std;

struct Component {
public:
  // this should be a type variable
  // OR systems could have a concept/requirements that determine if entity is
  // viewed
  Component *type
};
struct PositionComponent {};
struct TextureComponent {};
template <typename T> struct ObjectPool {
  vector<T> elements;
  vector<int> free_indexes;
  unordered_map<int, int> id_to_index;

  ObjectPool() {
    // since this is created with the world, should probably
    // populate elements with some initial components
    //
    // can have separate objectpools to limit # of things
    // eg number of particles shown
    //

    // pouplate free_indexes with every index of prefilled elements
  }

  void insert(T t) {
    if (free_indexes.size() > 0) {
      int index = free_indexes.back();
      free_indexes.pop_back();
      // should try to find the most efficient way to add t to elements
      // elements[index] = t;
      elements[index] = t.move();
    } else {
      int index = elements.size();
      id_to_index[t.id] = index;
      elements.push_back(t);
    }
  }
  void get(int id) { return elements[id_to_index(id)]; }
  void remove(int id) { // unlinks, doesnt erase
    id_to_index.erase(id);
    free_indexes.push_back(id);
  };
  struct Entity {

  public:
    // should register as callback or at compiletime
    // register puts this entity in the view list of systems that require its
    // components
    void register {}
  };

  struct System {
    // a system is INTERESTED in an entity if the entity has all the components
    // that the system finds INTERESTING
    virtual void update(
        // for entity : viewed_entities
        //
    );
  };
  struct DrawSystem : System {
    vector<Component *> reqs{PositionComponent, TextureComponent};
    // or could have 2 - reads and writes
    // vector<Component *> read_reqs{PositionComponent, TextureComponent};
    // vector<const Component *> write_reqs{};
    Component
        // needs to see certain components (tuple?)
        struct DrawSystem : System {
      update() override {
        for (auto entity : viewed_entities) {
          cout << "SDL_RenderCopy(render, ent.texture.texture, "
                  "ent.texture.source, ent.transform.dest)<<endl;"
          // OR
          // SDL_RenderCopy(render, textures[ent].texture, textures[ent] source,
          //                transforms[ent].dest);
        }

        // using the components that this system requires
        // do what must be done
        ;
        ;
      }
    };
    struct World {
      // need SystemRegistry
      // structure of each system and the components they find INTERESTING
      //
      // void RegisterEntity(Entity)
      // for(auto system:systems) {
      // if system.interesting_components is subset of Entity.components
      // system.viewed_entities << entity
      //...
      //
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
