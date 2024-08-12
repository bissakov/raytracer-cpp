#include <direct.h>
#include <src/main.h>
#include <tests/tests.h>
#include <windows.h>

#include <cassert>
#include <cstdio>

#if 0
struct Metrics {
  size_t total_allocated = 0;
  size_t total_freed = 0;

  size_t CurrentUsage() {
    return total_allocated - total_freed;
  }
};

static Metrics metrics;

void* operator new(size_t size) {
  metrics.total_allocated += size;
  return malloc(size);
}

void operator delete(void* memory, size_t size) noexcept {
  metrics.total_freed += size;
  free(memory);
}

void* operator new[](size_t size) {
  metrics.total_allocated += size;
  return malloc(size);
}

void operator delete[](void* memory, size_t size) noexcept {
  metrics.total_freed += size;
  free(memory);
}

static void PrintUsage() {
  std::cout << "Memory usage: " << metrics.CurrentUsage() << " bytes\n";
}
#endif

int main(int argc, char* argv[]) {
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
    char* root = argv[2];
    if (strcmp(root, ".") == 0) {
      char* cwd = _getcwd(NULL, 0);
      assert(cwd != NULL && "_getcwd error");
      root = cwd;
    }

    RunTests(root);

    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
