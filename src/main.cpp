#include <raylib/raylib.h>
#include <src/main.h>
#include <tests/tests.h>

#include <cstdio>
#include <cstdlib>
#include <string>

int main(int argc, char *argv[]) {
  if (argc > 2) {
    printf("Usage: raytracer [--test]\n");
    return EXIT_FAILURE;
  }

  if (argc == 2) {
    const std::string arg = argv[1];

    if (arg != "--test") {
      printf("Unknown command: %s\n", argv[1]);
      printf("Usage: raytracer [--test]\n");
      return EXIT_FAILURE;
    }

    RunTests();

    return EXIT_SUCCESS;
  }

  const int width = 200;
  const int height = 200;

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

  return EXIT_SUCCESS;
}
