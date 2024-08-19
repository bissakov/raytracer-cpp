#ifndef TESTS_TESTS_H_
#define TESTS_TESTS_H_

#include <geometry/point.h>
#include <geometry/vector.h>

#include <numbers>  // IWYU pragma: keep

#define PI std::numbers::pi

struct Projectile {
  Point position;
  Vector velocity;

  Projectile(const Point& position, const Vector& velocity) noexcept
      : position(position), velocity(velocity) {}
};

struct Environment {
  Vector gravity;
  Vector wind;

  Environment(const Vector& gravity, const Vector& wind) noexcept
      : gravity(gravity), wind(wind) {}
};

void RunTests(const char* root);

#endif  // TESTS_TESTS_H_
