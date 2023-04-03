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
      std::vector<std::unique_ptr<Object>>  objects;
    };
    
    struct Info
    {
      uint32_t              instances{};
      std::vector<Object>   objects{};
    };

    struct Properties
    {
      float                 deltaTime{};
      raylib::Vector2       dimensions{1920.f, 1080.f};
      raylib::Vector2       gRowCol{20.f, 10.f};
      std::vector<Cell>     grid{};
      spe::Vector           gravity{2.f, 180.f};
    };

    void Run();
    void Initialize(Properties&, const std::string&&);
    void Tick(Info&, Properties&);
    void LoadObject(Info&, Properties&, spe::Object&&);
    void UnloadObject(Info&, Properties&);
    void DrawObjects(const Info&);
    void TickObjects(Info&);
    void Gravity(Info&, const Properties&);
    void CheckCollisions(Info&);
    void ImpulseResolution(const spe::Object&, const spe::Object&);
    void InitializeGrid(Properties&);
    void UpdateCells(const Info&, Properties&);
    void LoadCell(Cell&, spe::Object&);
    bool CheckCell(Cell&, spe::Object&);
    bool CheckBounds(const spe::Object&, const Properties&);
  }
}

#endif // WORLD_HPP