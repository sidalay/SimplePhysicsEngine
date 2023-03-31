#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <array>
#include <string>

#include "object.hpp"

namespace spe 
{
  namespace world
  {
    struct Cell
    {
      int                   id{};
      raylib::Rectangle     area{};
    };

    struct Info
    {
      float                 deltaTime{};
      uint32_t              instances{};
      std::vector<Object>   objects{};
    };

    struct Properties
    {
      raylib::Vector2       dimensions{1920.f, 1080.f};
      raylib::Vector2       gRowCol{20.f, 10.f};
      std::vector<Cell>     grid{};
      spe::Vector           gravity{2.f, 180.f};
    };

    void Run();
    void Initialize(Properties&, const std::string&&);
    void Tick(Info&, const Properties&);
    void LoadObject(Info&, spe::Object&&);
    void UnloadObject(Info&, const Properties&);
    void DrawObjects(const Info&);
    void TickObjects(Info&);
    void Gravity(Info&, const Properties&);
    void CheckCollisions(Info&);
    void ImpulseResolution(const spe::Object&, const spe::Object&);
    void InitializeGrid(Properties&);
    bool CheckBounds(const spe::Object&, const Properties&);
  }
}

#endif // WORLD_HPP