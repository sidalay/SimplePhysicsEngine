#include "world.hpp"

float f(float t) {
  float v1 = t * t;
  float v2 = 1.f - (1.f - t) * (1.f - t);
  return std::lerp(v1, v2, t);
}

int main()
{
  // Initialization
  raylib::Vector2 window{800.f, 600.f};
  spe::World world{};
  // world.LoadObject({world.GetInstances()++, Shape::SQUARE, RigidBody::STATIC, {50.f,560.f}, {500.f,20.f}});
  float runningTime{};
  float t{};
  float x{};
  float direction{0.01};
  float directionX{0.01};

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
    if (x > 1.2f || x < 0.f) {
      directionX = -directionX;
    }
    t += direction;
    x += directionX;

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

    DrawRectangle(std::lerp(50, 500, x * x), 50, 20, 20, BLUE);
    DrawRectangle(std::lerp(50, 500, f(t)), 200, 20, 20, BLUE);
    DrawRectangle(std::lerp(50, 500, t * t), 350, 20, 20, BLUE);

    DrawRectangle(50, 500, 500, 20, { 
      static_cast<unsigned char>(std::lerp(0.f, 255.f, f(t))), 
      static_cast<unsigned char>(std::lerp(121.f, 20.f, f(t))), 
      static_cast<unsigned char>(std::lerp(241.f, 120.f, f(t))), 
      255 });

    DrawRectangle(50, 450, 100, 20, { 
      static_cast<unsigned char>(std::lerp(0.f, 255.f, 0.f)), 
      static_cast<unsigned char>(std::lerp(121.f, 20.f, 0.f)), 
      static_cast<unsigned char>(std::lerp(241.f, 120.f, 0.f)), 
      255 });
    DrawRectangle(150, 450, 100, 20, { 
      static_cast<unsigned char>(std::lerp(0.f, 255.f, .25f)), 
      static_cast<unsigned char>(std::lerp(121.f, 20.f, .25f)), 
      static_cast<unsigned char>(std::lerp(241.f, 120.f, .25f)), 
      255 });
    DrawRectangle(250, 450, 100, 20, { 
      static_cast<unsigned char>(std::lerp(0.f, 255.f, .50f)), 
      static_cast<unsigned char>(std::lerp(121.f, 20.f, .50f)), 
      static_cast<unsigned char>(std::lerp(241.f, 120.f, .50f)), 
      255 });
    DrawRectangle(350, 450, 100, 20, { 
      static_cast<unsigned char>(std::lerp(0.f, 255.f, .75f)), 
      static_cast<unsigned char>(std::lerp(121.f, 20.f, .75f)), 
      static_cast<unsigned char>(std::lerp(241.f, 120.f, .75f)), 
      255 });
    DrawRectangle(450, 450, 100, 20, { 
      static_cast<unsigned char>(std::lerp(0.f, 255.f, 1.f)), 
      static_cast<unsigned char>(std::lerp(121.f, 20.f, 1.f)), 
      static_cast<unsigned char>(std::lerp(241.f, 120.f, 1.f)), 
      255 });

    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}