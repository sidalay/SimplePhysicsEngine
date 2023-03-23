#include "world.hpp"

int main()
{
  // Initialization
  raylib::Vector2 window{800.f, 600.f};
  spe::World world{};
  // world.LoadObject({world.GetInstances()++, Shape::SQUARE, RigidBody::STATIC, {50.f,560.f}, {500.f,20.f}});
  float runningTime{};
  float t{};
  float direction{0.01};

  InitWindow(window.x, window.y, "Simple Physics Engine");
  SetTraceLogLevel(LOG_NONE);
  SetTargetFPS(144);

  // Main loop
  while (!WindowShouldClose())
  {
    // Update
    float deltaTime{GetFrameTime()};
    runningTime += deltaTime;

    if (t > 1.f || t < 0.f) {
      direction = -direction;
    }
    t += direction;

    if (runningTime > 1.f/33.5f) {
      world.EnforceGravity();
      world.TickObjects();
      world.Tick();
      runningTime = 0.f;
      
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        world.LoadObject({world.GetInstances()++, Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
      }
    }
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      world.LoadObject({world.GetInstances()++, Shape::SQUARE, RigidBody::DYNAMIC, GetMousePosition(), {20.f,20.f}});
    }

    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
      ToggleFullscreen();
    }

    // Draw
    BeginDrawing();

    world.DrawObjects();
    DrawRectangle(600, 0, 200, 800, Color{20, 21, 21, 255});
    // DrawRectangleLines(600, 0, 200, 800, Color{20, 21, 21, 255});
    DrawText(TextFormat("# of objects: %i", world.Instances()), 620, 20, 20, WHITE);
    DrawRectangle(std::lerp(100, 400, t), 300, 20, 20, BLUE);

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}