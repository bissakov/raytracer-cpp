#include <src/main.h>

#include <cassert>
#include <cstdio>

Point Point::operator+(const Vector &other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Point Point::operator-(const Vector &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Vector Point::operator-(const Point &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

bool Point::operator==(const Point &other) const {
  return (x == other.x && y == other.y && z == other.z);
}

bool Point::operator!=(const Point &p) const {
  return (x != p.x && y != p.y && z != p.z);
}

Vector Vector::operator+(const Vector &other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Vector Vector::operator-(const Vector &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

bool Vector::operator==(const Vector &other) const {
  return (x == other.x && y == other.y && z == other.z);
}

bool Vector::operator!=(const Vector &other) const {
  return (x != other.x && y != other.y && z != other.z);
}

Vector Vector::operator-() const {
  return {-x, -y, -z};
}

static inline void TestTupleAdd(float x1, float y1, float z1, float x2,
                                float y2, float z2) {
  Point left = {};
  left.x = x1;
  left.y = y1;
  left.z = z1;

  Vector right = {};
  right.x = x2;
  right.y = y2;
  right.z = z2;

  Point result = {};
  result = left + right;

  Point check = {};
  check.x = x1 + x2;
  check.y = y1 + y2;
  check.z = z1 + z2;

  assert(result == check);
  printf("Left: %.02f %.02f %.02f\n", left.x, left.y, left.z);
  printf("Right: %.02f %.02f %.02f\n", right.x, right.y, right.z);
  printf("TestTupleAdd: %.02f %.02f %.02f\n", result.x, result.y, result.z);
  printf("====================================\n\n");
}

static inline void TestTupleSubtract(float x1, float y1, float z1, float x2,
                                     float y2, float z2) {
  Point left = {};
  left.x = x1;
  left.y = y1;
  left.z = z1;

  Vector right = {};
  right.x = x2;
  right.y = y2;
  right.z = z2;

  Point result = {};
  result = left - right;

  Point check = {};
  check.x = x1 - x2;
  check.y = y1 - y2;
  check.z = z1 - z2;

  assert(result == check);
  printf("Left: %.02f %.02f %.02f\n", left.x, left.y, left.z);
  printf("Right: %.02f %.02f %.02f\n", right.x, right.y, right.z);
  printf("TestTupleSubtract: %.02f %.02f %.02f\n", result.x, result.y,
         result.z);
  printf("====================================\n\n");
}

int main(int argc, char *argv[]) {
  TestTupleAdd(3.0f, -2.0f, 5.0f, -2.0f, 3.0f, 1.0f);
  TestTupleSubtract(3.0f, 2.0f, 1.0f, -2.0f, 3.0f, 1.0f);

  return 0;
}
