#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "raylib-cpp.hpp"

enum class Shape 
{
  SQUARE, CIRCLE, TRIANGLE
};

enum class RigidBody
{
  STATIC, DYNAMIC
};

namespace spe 
{
  class Object 
  {
  public:
    Object(const uint32_t id, 
           const Shape shape, 
           const RigidBody body, 
           raylib::Vector2 pos, 
           raylib::Vector2 size);

    void Draw() const;
    [[nodiscard]] raylib::Vector2 GetPos() const {return m_pos;}
    [[nodiscard]] constexpr int GetId() const {return m_id;}

  private:
    const uint32_t      m_id{};
    const float         m_mass{};
    float               m_acceleration{};
    const Shape         m_shape{};
    const RigidBody     m_body{};
    raylib::Vector2     m_pos{};
    raylib::Vector2     m_size{};
    raylib::Vector2     m_direction{};
    std::vector<float>  m_velocity{};

    void CheckCollision();
  };
}

#endif // OBJECT_HPP