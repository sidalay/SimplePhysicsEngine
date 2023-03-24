#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cmath>

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
  struct Vector
  {
    float magnitude{};
    float direction{};
  };

  struct Scalar
  {
    float magnitude{};
  };

  class Object 
  {
  public:
    Object(const uint32_t id, 
           const Shape shape, 
           const RigidBody body, 
           raylib::Vector2 pos, 
           raylib::Vector2 size);

    void Tick();
    void Draw() const;
    void Push(const Vector force);
    [[nodiscard]] bool OutOfBounds() const;
    [[nodiscard]] RigidBody GetBody() const {return m_body;}
    [[nodiscard]] raylib::Vector2 GetPos() const {return m_pos;}
    [[nodiscard]] constexpr int GetId() const {return m_id;}

  private:
    uint32_t            m_id{};
    float               m_mass{};
    bool                m_colliding{};
    Shape               m_shape{};
    RigidBody           m_body{};
    raylib::Vector2     m_pos{};
    raylib::Vector2     m_size{};
    spe::Scalar         m_speed{};
    spe::Vector         m_acceleration{};
    spe::Vector         m_velocity{1,0};

    void CheckCollision();
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
[ ] Possibly rename Force struct
[ ] Apply Collision
[ ] Figure out how to add Mass into the formula
[ ] Revisit design
[ ] Implement lerp functions
*/ 