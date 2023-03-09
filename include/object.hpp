#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "raylib-cpp.hpp"

enum class Shape 
{
  SQUARE, CIRCLE
};

namespace spe 
{
  class Object 
  {
  public:
    Object(const uint32_t id, const Shape shape, raylib::Vector2 pos);

    void Draw() const;

  private:
    const uint32_t    m_id{};
    const float       m_weight{};
    const Shape       m_shape{};
    raylib::Vector2   m_pos{};
    raylib::Vector2   m_size{};
    raylib::Vector2   m_direction{};

    void CheckCollision();
  };
}

#endif // OBJECT_HPP