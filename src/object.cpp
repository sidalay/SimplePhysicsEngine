#include "object.hpp"

namespace spe 
{

  Object::Object(
    const uint32_t id, 
    const Shape shape, 
    raylib::Vector2 pos
  ) 
  : m_shape{shape}, m_pos{pos}, m_id{id} {
    
  }

  void Object::Draw() const {

  }

  void Object::CheckCollision() {
    
  }
}