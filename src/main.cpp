#include "world.hpp"

int main()
{
  // Initialization
  raylib::Vector2 window{800.f, 600.f};
  spe::World world{};
  world.LoadObject(spe::Object{0, Shape::SQUARE, RigidBody::DYNAMIC, {80.f,80.f}, {20.f, 20.f}});
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

    // Draw
    BeginDrawing();

    if (runningTime > 1.f/30.f) {
      world.EnforceGravity();
      world.TickObjects();
      world.Tick();
      runningTime = 0.f;
    }

    world.DrawObjects();
    DrawText(TextFormat("# of objects: %i", world.Instances()), 620, 20, 20, WHITE);

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}