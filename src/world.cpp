#include <algorithm>
#include <iostream>

#include "world.hpp"

namespace spe 
{
  namespace world
  {
    using namespace spe;

    void Run() 
    {
      Properties properties{};
      Initialize(properties, "Simple Physics Engine");

      if (IsWindowReady())  {
        while (!WindowShouldClose()) {
          Tick(properties);
        }
      }

      CloseWindow();
    }

    void Initialize(Properties& global, const std::string&& title)
    {
      SetTraceLogLevel(LOG_WARNING);
      InitWindow(global.dimensions.x, global.dimensions.y, title.c_str());
      InitializeGrid(global);
      SetTargetFPS(144);
    }

    void Tick(Properties& global)
    {
      // Update
      global.deltaTime += GetFrameTime();

      if (global.deltaTime > 1.f/24.f) {
        global.deltaTime = 0.f;
        Gravity(global);
        TickObjects(global);
        UnloadObject(global);
        UpdateCells(global);

        if (spe::blend > 1.f || spe::blend < 0.f) {
          spe::direction = -spe::direction;
        }
        spe::blend += spe::direction;
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
          LoadObject(global, {global.instances++, Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
        }
      }
      
      if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        LoadObject(global, {global.instances++, Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
      }

      if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
        ToggleFullscreen();
      }

      // Draw
      BeginDrawing();

      DrawGrid(global);

      DrawObjects(global);
      // DrawText(TextFormat("# of instances: %i", global.instances), 20, 120, 20, WHITE);

      // ------------- Lerp
      // DrawRectangle(spe::Lerp(global.dimensions.x * .05f, global.dimensions.x * .9f, spe::EaseIn(spe::blend)), 100, 20, 20, BLUE);
      // DrawRectangle(spe::Lerp(global.dimensions.x * .05f, global.dimensions.x * .9f, spe::EaseOut(spe::blend)), 250, 20, 20, BLUE);
      // DrawRectangle(spe::Lerp(global.dimensions.x * .05f, global.dimensions.x * .9f, spe::Smoothstep(spe::blend)), 400, 20, 20, BLUE);

      // DrawRectangle(global.dimensions.x * .05f, 550, global.dimensions.x * .9f, 20, { 
      //   static_cast<unsigned char>(spe::Lerp(0.f, 255.f, spe::Smoothstep(spe::blend))), 
      //   static_cast<unsigned char>(spe::Lerp(121.f, 20.f, spe::Smoothstep(spe::blend))), 
      //   static_cast<unsigned char>(spe::Lerp(241.f, 120.f, spe::Smoothstep(spe::blend))), 
      //   255 
      // });
      // ------------- Lerp

      ClearBackground(BLACK);
      EndDrawing();
    }

    void LoadObject(Properties& global, spe::Object&& object)
    {
      for (auto& cell : global.grid) {
        if (LoadCell(cell, object)) {
          return;
        }
      } 
    }

    void UnloadObject(Properties& global)
    {
      for (auto& cell : global.grid) {
        auto it {std::remove_if(cell.objects.begin(), cell.objects.end(), [&](const Object& object) {
          return CheckBounds(object, global);
        })};
        cell.objects.erase(it, cell.objects.end());
      }
    }

    void DrawObjects(const Properties& global)
    {
      for (auto& cell : global.grid) {
        for (auto& object : cell.objects) {
          object.Draw();
        }
      }
    }

    void DrawGrid(const Properties& global)
    {
      for (auto& cell : global.grid) {
        DrawRectangleLines(cell.area.x, cell.area.y, cell.area.width, cell.area.height, { 255, 255, 255, 100 });
        DrawText(TextFormat("%i", cell.id), cell.area.x+5, cell.area.y+5, 20, { 255, 255, 255, 100 });
        DrawText(TextFormat("%i", cell.objects.size()), cell.area.x+5, cell.area.y+30, 20, RED);
      }
    }

    void TickObjects(Properties& global)
    {
      for (auto& cell : global.grid) {
        for (auto& object : cell.objects) {
          object.Tick();
        }
      }
    }

    bool CheckBounds(const Object& object, const Properties& global)
    {
      Vector2 pos{object.GetPos()};
      if (pos.x < 0 || pos.x > global.dimensions.x || pos.y < 0 || pos.y > global.dimensions.y) {
        return true;
      }
      return false;
    }

    void Gravity(Properties& global)
    {
      for (auto& cell : global.grid) {
        for (auto& object : cell.objects) {
          if (object.GetBody() == RigidBody::DYNAMIC) {
            object.Push(global.gravity);
          }
        }
      }
    }

    void CheckCollisions(Properties& global)
    {
      // for (int i{}; i < info.objects.size(); ++i) {
      //   if (CheckCollisionRecs(info.objects[i].GetRect(), info.objects[i+1].GetRect())) {
      //     ImpulseResolution(info.objects[i], info.objects[i+1]);
      //   }
      // }
    }

    void InitializeGrid(Properties& global)
    {
      int id{};
      global.grid.reserve(200);
      for (float y{}; y < global.dimensions.y; y += global.dimensions.y/global.gRowCol.y) {
        for (float x{}; x < global.dimensions.x; x += global.dimensions.x/global.gRowCol.x) {
          global.grid.emplace_back(id++, Rectangle{x, y, global.dimensions.x/global.gRowCol.x, global.dimensions.y/global.gRowCol.y});
        }
      }
    }

    bool LoadCell(Cell& cell, Object& object)
    {
      if (CheckCell(cell, object)) 
      {
        cell.objects.emplace_back(std::move(object));
        return true;
      }
      return false;
    }

    void UpdateCells(Properties& global)
    {
      for (int y{}; y < global.gRowCol.y; ++y) {
        for (int x{}; x < global.gRowCol.x; ++x) {
          int index{x + (y * static_cast<int>(global.gRowCol.x))};
          for (auto it{global.grid[index].objects.begin()}; it != global.grid[index].objects.end(); ++it) {
            auto& object{*it};
            // check same cell
            if (CheckCell(global.grid[index], object)) {
              continue;
            } else {
              // check adjacent Cells
              // INNER CELLS
              if ((x > 0 && y > 0) && (x < global.gRowCol.x && y < global.gRowCol.y)) {
                if (CheckCell(global.grid[index-(global.gRowCol.x-1)], object)) {
                  global.grid[index-(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-global.gRowCol.x], object)) {
                  global.grid[index-global.gRowCol.x].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x+1)], object)) {
                  global.grid[index-(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-1], object)) {
                  global.grid[index-1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+1], object)) {
                  global.grid[index+1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x+1)], object)) {
                  global.grid[index+(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+global.gRowCol.x], object)) {
                  global.grid[index+global.gRowCol.x].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x-1)], object)) {
                  global.grid[index+(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                }
              } 
              // CORNER CELLS
              else if (index == 0) {
                if (CheckCell(global.grid[index+1], object)) {
                  global.grid[index+1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x)], object)) {
                  global.grid[index+(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x+1)], object)) {
                  global.grid[index+(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                }
              } else if (index == global.gRowCol.x - 1.f) {
                if (CheckCell(global.grid[index-1], object)) {
                  global.grid[index-1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x)], object)) {
                  global.grid[index+(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x-1)], object)) {
                  global.grid[index+(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                }
              } else if (index == global.gRowCol.x * (global.gRowCol.y - 1)) {
                if (CheckCell(global.grid[index+1], object)) {
                  global.grid[index+1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x)], object)) {
                  global.grid[index-(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x-1)], object)) {
                  global.grid[index-(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                }
              } else if (index == (global.gRowCol.x * global.gRowCol.y) - 1.f) {
                if (CheckCell(global.grid[index-1], object)) {
                  global.grid[index-1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x)], object)) {
                  global.grid[index-(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x+1)], object)) {
                  global.grid[index-(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                }
              } 
              // BORDER CELLS
              else if (y == 0 && (x != 0 && x != global.gRowCol.x - 1)) {
                if (CheckCell(global.grid[index-1], object)) {
                  global.grid[index-1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+1], object)) {
                  global.grid[index+1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x-1)], object)) {
                  global.grid[index+(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x)], object)) {
                  global.grid[index+(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x+1)], object)) {
                  global.grid[index+(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                }
              } else if (y == global.gRowCol.y-1) {
                if (CheckCell(global.grid[index-1], object)) {
                  global.grid[index-1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+1], object)) {
                  global.grid[index+1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x-1)], object)) {
                  global.grid[index-(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x)], object)) {
                  global.grid[index-(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x+1)], object)) {
                  global.grid[index-(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                }
              } else if (x == 0) {
                if (CheckCell(global.grid[index+1], object)) {
                  global.grid[index+1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x)], object)) {
                  global.grid[index+(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x+1)], object)) {
                  global.grid[index+(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x)], object)) {
                  global.grid[index-(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x-1)], object)) {
                  global.grid[index-(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                }
              } else if (x == global.gRowCol.x-1) {
                if (CheckCell(global.grid[index-1], object)) {
                  global.grid[index-1].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x)], object)) {
                  global.grid[index-(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index-(global.gRowCol.x+1)], object)) {
                  global.grid[index-(global.gRowCol.x+1)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x)], object)) {
                  global.grid[index+(global.gRowCol.x)].objects.emplace_back(std::move(object));
                } else if (CheckCell(global.grid[index+(global.gRowCol.x-1)], object)) {
                  global.grid[index+(global.gRowCol.x-1)].objects.emplace_back(std::move(object));
                }
              }
              global.grid[index].objects.erase(it--);
            }
          }
        }
      }
    }

    bool CheckCell(Cell& cell, Object& object) 
    {
      if ((object.GetPos().x >= cell.area.x) && 
          (object.GetPos().x <= cell.area.x + cell.area.width) &&
          (object.GetPos().y >= cell.area.y) && 
          (object.GetPos().y <= cell.area.y + cell.area.height)) 
      {
        return true;
      }
      return false;
    }

    void ImpulseResolution(const Object& objone, const Object& objtwo)
    {

    }
  }
}