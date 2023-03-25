#ifndef WORLD2_HPP
#define WORLD2_HPP

#include <vector>
#include <array>
#include <algorithm>

#include "object.hpp"

namespace spe 
{
  namespace world
  {
    struct Info
    {
      uint32_t              instances{};
      std::vector<Object>   objects{};
    };

    struct Properties
    {
      raylib::Vector2       dimensions{1920.f, 1080.f};
      spe::Vector           gravity{2.f, 180.f};
    };

    void Run();
    void Initialize();
    void Tick();
    void UnloadObject();
    void DrawObjects();
    void TickObjects();
  }
}

#endif // WORLD2_HPP