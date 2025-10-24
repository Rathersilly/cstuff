// ECS based on Tim Ford's Overwatch GDC talk
#include <array>
#include <cstdint>
#include <unordered_map>
using namespace std;
using EntityID = uint32_t;

struct Component {
  void Create(/* resource* */) {}
  ~Component();
};
class Entity {
  EntityID id;
  array<Component *, 16> components;
};

class System {

  void update() {}
};
template <typename C> struct ObjectPool {};

class EntityAdmin {
  array<System *, 16> systems;
  unordered_map<EntityID, Entity *> entities;
  ObjectPool<Component> *object_pool;
  array<Component *, 16> *components;
};

struct PhysicsTuple {
  DynamicPhysicsComponent *m_dynamic_physics;
  TransformComponent *m_transform;
  ContactListComponent *m_contacts;
};

void PhysicsSystem::Tick(f32 timestep) { // Write transforms of physics objects
  for (PhysicsTuple &t : GetPhysicsTuples()) {
    IPhysicsProxy *proxy = pw->GetProxy(t.m_dynamicPhysics->m_proxy);

    CopyTransform(t.m_transform, proxy);
    CopyContacts(t.m_contacts, proxy);
  }
}
