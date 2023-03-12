#include "world.hpp"

namespace spe 
{
  Gaia::Gaia() {

  }

  void Gaia::LoadObject(Object object) {
    m_objects.emplace_back(object);
  }

  void Gaia::DrawObjects() const
  {
    for (auto& object : m_objects) {
      object.Draw();
    }
  }
}