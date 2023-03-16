#include "object.hpp"

namespace spe 
{

  Object::Object(
    const uint32_t id, 
    const Shape shape,
    const RigidBody body, 
    raylib::Vector2 pos,
    raylib::Vector2 size
  ) 
  : m_id{id}, m_shape{shape}, m_body{body}, m_pos{pos}, m_size{size} {
    
  }

  void Object::Tick()
  {
    UpdatePos();
  }

  void Object::Draw() const
  {
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

  void Object::Push(const Force force)
  {
    m_acceleration = force.magnitude;
    if (!m_colliding && m_velocity.magnitude < 25.f) {
      m_velocity.magnitude += m_acceleration;
      m_velocity.direction = force.direction;
    }
  }

  bool Object::OutOfBounds() const
  {
    if (m_pos.x < 0 || m_pos.x > 600 + m_size.x || m_pos.y < 0 || m_pos.y > 600) {
      return true;
    }
    return false;
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

  void Object::UpdatePos()
  {
    m_pos.y += m_velocity.magnitude;
  }
}