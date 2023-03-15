#include "world.hpp"

int main()
{
  // Initialization
  raylib::Vector2 window{800.f, 600.f};
  spe::World world{};
  float runningTime{};

  InitWindow(window.x, window.y, "Simple Physics Engine");
  SetTraceLogLevel(LOG_NONE);
  SetTargetFPS(144);

  // Main loop
  while (!WindowShouldClose())
  {
    // Update
    float deltaTime{GetFrameTime()};
    runningTime += deltaTime;

    if (runningTime > 1.f/30.f) {
      world.EnforceGravity();
      world.TickObjects();
      world.Tick();
      runningTime = 0.f;
      
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        world.LoadObject(spe::Object{world.GetInstances(), Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
        ++(world.GetInstances());
      }
    }
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      world.LoadObject(spe::Object{world.GetInstances(), Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
      ++(world.GetInstances());
    }


    // Draw
    BeginDrawing();

    world.DrawObjects();
    DrawText(TextFormat("# of objects: %i", world.Instances()), 620, 20, 20, WHITE);

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}