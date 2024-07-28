#ifndef TESTS_TESTS_H_
#define TESTS_TESTS_H_

#include <src/point_vector.h>

#include <string>

struct Projectile {
  Point position;
  Vector velocity;
};

struct Environment {
  Vector gravity;
  Vector wind;
};

void RunTests(std::string root_folder_path);

#endif  // TESTS_TESTS_H_
