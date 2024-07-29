#include <src/main.h>
#include <tests/tests.h>
#include <windows.h>

#include <cstdio>
#include <string>

int main(int argc, char *argv[]) {
  if (argc < 3 || argc > 4 || strcmp(argv[1], "--root") != 0) {
    printf("\nUsage: raytracer [--root --test]\n");
    return EXIT_FAILURE;
  }

  if (GetFileAttributesA(argv[2]) == INVALID_FILE_ATTRIBUTES) {
    printf("\nUsage: raytracer [--root --test]\n");
    printf("\nInvalid root folder path: %s\n", argv[2]);
    return EXIT_FAILURE;
  }

  if (argc == 4 && strcmp(argv[3], "--test") == 0) {
    std::string root_folder_path = argv[2];
    RunTests(root_folder_path);
    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
