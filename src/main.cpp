#include <raylib/raylib.h>
#include <src/main.h>

int main(int argc, char *argv[]) {
  const int width = 1920;
  const int height = 1080;
  const int target_fps = 60;

  InitWindow(width, height, "Ray tracer");

  SetTargetFPS(target_fps);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("hello world!", 200, 200, 16, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
