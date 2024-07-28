#ifndef TESTS_TEST_CANVAS_H_
#define TESTS_TEST_CANVAS_H_

#include <src/canvas.h>
#include <src/point_vector.h>
#include <src/test_suite.h>

struct Projectile {
  Point position;
  Vector velocity;
};

struct Environment {
  Vector gravity;
  Vector wind;
};

void TestCanvas(TestFramework *framework);

#endif  // TESTS_TEST_CANVAS_H_
