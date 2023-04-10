#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "raylib.h"
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
    Object(const int id,
           const Shape shape, 
           const RigidBody body, 
           Vector2 pos, 
           Vector2 size);
    ~Object() = default;
    Object(const Object&) = delete;
    Object(Object&&) = default;
    Object& operator=(const Object&) = delete;
    Object& operator=(Object&&) = default;

    void Tick();
    void Draw() const;
    void Push(const spe::Vector force);
    [[nodiscard]] RigidBody         GetBody() const {return m_body;}
    [[nodiscard]] Vector2           GetPos()  const {return m_pos;}
    [[nodiscard]] constexpr int     GetId()   const {return m_id;}
    [[nodiscard]] Rectangle         GetRect() const {return m_rect;}

  private:
    int                 m_id{};
    bool                m_colliding{};
    Shape               m_shape{};
    RigidBody           m_body{};
    Vector2             m_pos{};
    Vector2             m_size{};
    Rectangle           m_rect{};
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