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
      UnloadObject(info);

      if (spe::blend > 1.f || spe::blend < 0.f) {
        info.direction = -info.direction;
      }
      spe::blend += info.direction;

      if (info.deltaTime > 1.f/33.5f) {
        Gravity(info, global);
        TickObjects(info);
        info.deltaTime = 0.f;
        
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

      DrawRectangle(spe::Lerp(50, 500, spe::EaseIn(spe::blend)), 50, 20, 20, BLUE);
      DrawRectangle(spe::Lerp(50, 500, spe::QuadraticEaseOut(spe::blend)), 200, 20, 20, BLUE);
      DrawRectangle(spe::Lerp(50, 500, spe::Smoothstep(spe::blend)), 350, 20, 20, BLUE);

      DrawRectangle(50, 500, 500, 20, { 
        static_cast<unsigned char>(spe::Lerp(0.f, 255.f, spe::Smoothstep(spe::blend))), 
        static_cast<unsigned char>(spe::Lerp(121.f, 20.f, spe::Smoothstep(spe::blend))), 
        static_cast<unsigned char>(spe::Lerp(241.f, 120.f, spe::Smoothstep(spe::blend))), 
        255 
      });

      ClearBackground(BLACK);
      EndDrawing();
    }

    void LoadObject(world::Info& info, Object&& object)
    {
      info.objects.emplace_back(object);
    }

    void UnloadObject(world::Info& info)
    {
      auto it {std::remove_if(info.objects.begin(), info.objects.end(), [](const Object& object) {
        return object.OutOfBounds();
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