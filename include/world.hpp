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
    using namespace spe;

    struct Info
    {
      float deltaTime{};
      float t{};
      float direction{0.01};
      uint32_t              instances{};
      std::vector<Object>   objects{};
    };

    struct Properties
    {
      raylib::Vector2       dimensions{1280.f, 720.f};
      spe::Vector           gravity{2.f, 180.f};
    };

    void Run();
    void Initialize(const world::Properties&, const std::string&&);
    void Tick(world::Info&, const world::Properties&);
    void LoadObject(world::Info&, Object&&);
    void UnloadObject(world::Info&);
    void DrawObjects(const world::Info&);
    void TickObjects(world::Info&);
    void Gravity(world::Info&, const world::Properties&);
  }
}

#endif // WORLD_HPP