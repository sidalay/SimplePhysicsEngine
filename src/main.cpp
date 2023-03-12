#include "world.hpp"

int main(void)
{
  // Initialization
  raylib::Vector2 window{800.f, 600.f};
  spe::Gaia gaia{};
  gaia.LoadObject(spe::Object{0, Shape::SQUARE, {80.f,80.f}, {20.f, 20.f}});

  InitWindow(window.x, window.y, "Simple Physics Engine");
  SetTraceLogLevel(LOG_NONE);
  SetTargetFPS(144);

  // Main loop
  while (!WindowShouldClose())
  {
    // Update
    
    // Draw
    BeginDrawing();

    gaia.DrawObjects();

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}