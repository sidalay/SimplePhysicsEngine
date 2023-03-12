#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <array>

#include "object.hpp"

namespace spe 
{
  class Gaia 
  {

  public:
    Gaia();

    void LoadObject(Object object);
    void DrawObjects() const;
    const std::vector<Object>& GetObjects() {return m_objects;}
    
  private:
    float               m_gravity{};
    int                 m_total{};
    std::array<int, 3>  m_count{};
    std::vector<Object> m_objects{};
    raylib::Vector2     m_world{600.f, 600.f};
  };
}

#endif // WORLD_HPP