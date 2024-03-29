#include "object.hpp"

namespace spe 
{

  Object::Object(
    const int id,
    const Shape shape,
    const RigidBody body, 
    Vector2 pos,
    Vector2 size
  ) 
  : m_id{id}, 
    m_shape{shape}, 
    m_body{body},
    m_pos{pos}, 
    m_size{size},
    m_rect{pos.x, pos.y, size.x, size.y}
  {

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
        DrawRectangleLines(m_pos.x-1, m_pos.y-1, m_size.x+2, m_size.y+2, WHITE);
        break;
      case Shape::CIRCLE:
        break;
      case Shape::TRIANGLE:
        break;
    };
  }

  void Object::Push(const spe::Vector force)
  {
    m_acceleration.magnitude = force.magnitude;
    if (!m_colliding && m_velocity.magnitude < 25.f) {
      m_velocity.magnitude += m_acceleration.magnitude;
      m_velocity.direction = force.direction;
    }
  }

  void Object::UpdatePos()
  {
    m_pos.y += m_velocity.magnitude;
  }
}