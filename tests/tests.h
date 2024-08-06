#ifndef TESTS_TESTS_H_
#define TESTS_TESTS_H_

#include <src/point_vector.h>

#include <numbers>  // IWYU pragma: keep
#include <string>

#define PI std::numbers::pi

struct Projectile {
  Point position;
  Vector velocity;
};

struct Environment {
  Vector gravity;
  Vector wind;
};

void RunTests(const std::string root_folder_path);

#endif  // TESTS_TESTS_H_
