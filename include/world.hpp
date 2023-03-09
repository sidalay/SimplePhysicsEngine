#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "object.hpp"

namespace spe 
{
  class Gaia 
  {

  public:
    Gaia();

    void LoadObject(Shape shape);
    
  private:
    float               m_gravity{};
    int                 m_instances{};
    std::vector<Object> m_objects{};
    raylib::Vector2     m_world{600.f, 600.f};
  };
}

#endif // WORLD_HPP