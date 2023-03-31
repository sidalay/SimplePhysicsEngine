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
    struct Section
    {
      int                   region{};
      raylib::Vector2       width{};
      raylib::Vector2       height{};
      raylib::Rectangle     rect{};
    };

    struct Info
    {
      float                 deltaTime{};
      uint32_t              instances{};
      std::vector<Object>   objects{};
    };

    struct Properties
    {
      raylib::Vector2       dimensions{1280.f, 720.f};
      spe::Vector           gravity{2.f, 180.f};
      std::vector<Section>  grid{};
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
    bool CheckBounds(const spe::Object&, const Properties&);
  }
}

#endif // WORLD_HPP