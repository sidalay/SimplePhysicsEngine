#include "world.hpp"

int main(void)
{
  // Initialization
  raylib::Vector2 window{800.f, 600.f};
  spe::Gaia gaia{};

  InitWindow(window.x, window.y, "Simple Physics Engine");
  SetTraceLogLevel(LOG_NONE);
  SetTargetFPS(144);

  // Main loop
  while (!WindowShouldClose())
  {
    // Update
    
    // Draw
    BeginDrawing();

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}