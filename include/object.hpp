#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "raylib-cpp.hpp"
#include "lerp.hpp"

#include <vector>

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
  using Scalar = float;

  struct Vector
  {
    float magnitude{};
    float direction{};
  };

  class Object 
  {
  public:
    Object(const uint32_t id,
           const Shape shape, 
           const RigidBody body, 
           raylib::Vector2 pos, 
           raylib::Vector2 size);
    ~Object() = default;
    Object(const Object&) = delete;
    Object(Object&&) = default;
    Object& operator=(const Object&) = delete;
    Object& operator=(Object&&) = default;

    void Tick();
    void Draw() const;
    void Push(const spe::Vector force);
    [[nodiscard]] RigidBody         GetBody() const {return m_body;}
    [[nodiscard]] raylib::Vector2   GetPos()  const {return m_pos;}
    [[nodiscard]] constexpr int     GetId()   const {return m_id;}
    [[nodiscard]] raylib::Rectangle GetRect() const {return m_rect;}

  private:
    uint32_t            m_id{};
    bool                m_colliding{};
    Shape               m_shape{};
    RigidBody           m_body{};
    raylib::Vector2     m_pos{};
    raylib::Vector2     m_size{};
    raylib::Rectangle   m_rect{};
    spe::Scalar         m_mass{};
    spe::Scalar         m_speed{};
    spe::Vector         m_force{};
    spe::Vector         m_acceleration{};
    spe::Vector         m_velocity{};

    void UpdatePos();
  };
}

// meters/s
// gravity = 2 m/s/s
// 1 meter = 1 pixel
// world origin 0,0 = top left

#endif // OBJECT_HPP

/*
TODO
[x] Possibly rename Force -> Vector
[ ] Apply Collision
[ ] Figure out how to add Mass into the formula
[ ] Revisit design
[ ] Implement lerp functions
*/ 