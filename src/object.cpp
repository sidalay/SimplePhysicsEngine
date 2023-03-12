#include "object.hpp"

namespace spe 
{

  Object::Object(
    const uint32_t id, 
    const Shape shape, 
    raylib::Vector2 pos,
    raylib::Vector2 size
  ) 
  : m_id{id}, m_shape{shape}, m_pos{pos}, m_size{size} {
    
  }

  void Object::Draw() const {
    switch (m_shape)
    {
      case Shape::SQUARE:
        DrawRectangleLines(m_pos.x, m_pos.y, m_size.x, m_size.y, WHITE);
        break;
      case Shape::CIRCLE:
        break;
      case Shape::TRIANGLE:
        break;
    };
  }

  void Object::CheckCollision() {
    switch (m_shape)
    {
      case Shape::SQUARE:
        break;
      case Shape::CIRCLE:
        break;
      case Shape::TRIANGLE:
        break;
    };
  }
}