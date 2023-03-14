#include "world.hpp"

namespace spe 
{
  World::World() {

  }

  void World::Tick()
  {
    UnloadObject();
  }

  void World::LoadObject(Object object)
  {
    m_objects.emplace_back(object);
  }

  void World::UnloadObject()
  {
    auto it {std::remove_if(m_objects.begin(), m_objects.end(), [](const Object& object) {
      return object.OutOfBounds();
    })};
    m_objects.erase(it, m_objects.end());
  }

  void World::DrawObjects() const
  {
    for (auto& object : m_objects) {
      object.Draw();
    }
  }

  void World::TickObjects()
  {
    for (auto& object : m_objects) {
      object.Tick();
    }
  }

  void World::EnforceGravity()
  {
    for (auto& object : m_objects) {
      object.Push(m_gravity);
    }
  }
}