#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "raylib-cpp.hpp"

enum class Shape 
{
  SQUARE, CIRCLE, TRIANGLE
};

namespace spe 
{
  class Object 
  {
  public:
    Object(const uint32_t id, const Shape shape, raylib::Vector2 pos);

    void Draw() const;
    [[nodiscard]] raylib::Vector2 GetPos() const {return m_pos;}
    [[nodiscard]] constexpr int GetId() const {return m_id;}

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