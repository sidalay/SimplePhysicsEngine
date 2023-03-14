#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <array>
#include <algorithm>

#include "object.hpp"

namespace spe 
{
  class World 
  {

  public:
    World();

    void Tick();
    void LoadObject(Object object);
    void UnloadObject();
    void DrawObjects() const;
    void TickObjects();
    void EnforceGravity();
    const std::vector<Object>& GetObjects() {return m_objects;}
    const int Instances() {return m_objects.size();}
    
  private:
    const Force         m_gravity{2.f, 180.f};
    int                 m_total{};
    std::array<int, 3>  m_count{};
    std::vector<Object> m_objects{};
    raylib::Vector2     m_world{600.f, 600.f};
  };
}

#endif // WORLD_HPP