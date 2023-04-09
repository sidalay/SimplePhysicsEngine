#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <memory>

#include "object.hpp"

namespace spe 
{
  namespace world
  {
    struct Cell
    {
      uint16_t              id{};
      raylib::Rectangle     area{};
      std::vector<Object>   objects;
    };
  
    struct Properties
    {
      float                 deltaTime{};
      uint32_t              instances{};
      raylib::Vector2       dimensions{1280.f, 720.f};
      raylib::Vector2       gRowCol{3.f, 3.f};
      std::vector<Cell>     grid{};
      spe::Vector           gravity{2.f, 180.f};
    };

    void Run();
    void Initialize(Properties&, const std::string&&);
    void Tick(Properties&);
    void LoadObject(Properties&, spe::Object&&);
    void UnloadObject(Properties&);
    void DrawObjects(const Properties&);
    void DrawGrid(const Properties&);
    void TickObjects(Properties&);
    void Gravity(Properties&);
    void CheckCollisions(Properties&);
    void ImpulseResolution(const spe::Object&, const spe::Object&);
    void InitializeGrid(Properties&);
    void UpdateCells(Properties&);
    bool LoadCell(Cell&, spe::Object&);
    bool CheckCell(Cell&, spe::Object&);
    bool CheckBounds(const spe::Object&, const Properties&);
  }
}

#endif // WORLD_HPP