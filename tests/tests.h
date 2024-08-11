#ifndef TESTS_TESTS_H_
#define TESTS_TESTS_H_

#include <src/point_vector.h>

#include <numbers>  // IWYU pragma: keep

#define PI std::numbers::pi

struct Projectile {
  Point position;
  Vector velocity;
};

struct Environment {
  Vector gravity;
  Vector wind;
};

void RunTests(const char* root);

#endif  // TESTS_TESTS_H_
