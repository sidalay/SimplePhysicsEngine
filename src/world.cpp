#include <algorithm>

#include "world.hpp"
#include "lerp.hpp"


namespace spe 
{
  namespace world
  {
    using namespace spe;

    void Run() 
    {
      world::Info info{};
      world::Properties properties{};
      world::Initialize(properties, "Simple Physics Engine");

      if (IsWindowReady())  {
        while (!WindowShouldClose()) {
          spe::world::Tick(info, properties);
        }
      }

      CloseWindow();
    }

    void Initialize(const world::Properties& global, const std::string&& title)
    {
      SetTraceLogLevel(LOG_WARNING);
      InitWindow(global.dimensions.x, global.dimensions.y, title.c_str());
      SetTargetFPS(144);
    }

    void Tick(world::Info& info, const world::Properties& global)
    {
      // Update
      info.deltaTime += GetFrameTime();
      UnloadObject(info, global);

      if (info.deltaTime > 1.f/144.f) {
        Gravity(info, global);
        TickObjects(info);
        info.deltaTime = 0.f;

        if (spe::blend > 1.f || spe::blend < 0.f) {
          spe::direction = -spe::direction;
        }
        spe::blend += spe::direction;
        
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
          LoadObject(info, {info.instances++, Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
        }
      }
      
      if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        LoadObject(info, {info.instances++, Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
      }

      if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
        ToggleFullscreen();
      }

      // Draw
      BeginDrawing();

      DrawObjects(info);
      DrawText(TextFormat("# of objects: %i", info.objects.size()), 20, 20, 20, WHITE);
      DrawText(TextFormat("# of instances: %i", info.instances), 20, 40, 20, WHITE);

      // ------------- Lerp
      DrawRectangle(spe::Lerp(global.dimensions.x * .05f, global.dimensions.x * .9f, spe::EaseIn(spe::blend)), 100, 20, 20, BLUE);
      DrawRectangle(spe::Lerp(global.dimensions.x * .05f, global.dimensions.x * .9f, spe::EaseOut(spe::blend)), 250, 20, 20, BLUE);
      DrawRectangle(spe::Lerp(global.dimensions.x * .05f, global.dimensions.x * .9f, spe::Smoothstep(spe::blend)), 400, 20, 20, BLUE);

      DrawRectangle(global.dimensions.x * .05f, 550, global.dimensions.x * .9f, 20, { 
        static_cast<unsigned char>(spe::Lerp(0.f, 255.f, spe::Smoothstep(spe::blend))), 
        static_cast<unsigned char>(spe::Lerp(121.f, 20.f, spe::Smoothstep(spe::blend))), 
        static_cast<unsigned char>(spe::Lerp(241.f, 120.f, spe::Smoothstep(spe::blend))), 
        255 
      });
      // ------------- Lerp

      ClearBackground(BLACK);
      EndDrawing();
    }

    void LoadObject(world::Info& info, Object&& object)
    {
      info.objects.emplace_back(object);
    }

    void UnloadObject(world::Info& info, const world::Properties& global)
    {
      auto it {std::remove_if(info.objects.begin(), info.objects.end(), [&](const Object& object) {
        return CheckBounds(object, global);
      })};
      info.objects.erase(it, info.objects.end());
    }

    void DrawObjects(const world::Info& info)
    {
      for (auto& object : info.objects) {
        object.Draw();
      }
    }

    void TickObjects(world::Info& info)
    {
      for (auto& object : info.objects) {
        object.Tick();
      }
    }

    bool CheckBounds(const Object& object, const world::Properties& global)
    {
      raylib::Vector2 pos{object.GetPos()};
      if (pos.x < 0 || pos.x > global.dimensions.x || pos.y < 0 || pos.y > global.dimensions.y) {
        return true;
      }
      return false;
    }

    void Gravity(world::Info& info, const world::Properties& global)
    {
      for (auto& object : info.objects) {
        if (object.GetBody() == RigidBody::DYNAMIC) {
          object.Push(global.gravity);
        }
      }
    }
  }
}