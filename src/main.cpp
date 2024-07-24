#include "../src/main.h"

#include <cassert>
#include <cstdio>

static inline bool TupleEqual(Tuple *left, Tuple *right) {
  return (left->x == right->x) && (left->y == right->y) &&
         (left->z == right->z) && (left->w == right->w);
}

static inline Tuple TupleAdd(Tuple *left, Tuple *right) {
  Tuple result = {};
  result.x = left->x + right->x;
  result.y = left->y + right->y;
  result.z = left->z + right->z;
  result.w = left->w + right->w;
  return result;
}

static inline Tuple TupleSubtract(Tuple *left, Tuple *right) {
  Tuple result = {};
  result.x = left->x - right->x;
  result.y = left->y - right->y;
  result.z = left->z - right->z;
  result.w = left->w - right->w;
  return result;
}

static inline Tuple TupleNegate(Tuple *tuple) {
  Tuple zero = {};
  Tuple result = {};
  result = TupleSubtract(&zero, tuple);
  return result;
}

static inline bool TestTupleVector(float x, float y, float z) {
  Tuple point = {};
  point.x = x;
  point.y = y;
  point.z = z;
  point.w = 1.0f;

  if (point.w != 1.0f) {
    printf("point.w is not 1.0f\n");
    return false;
  }

  Tuple vector = {};
  vector.x = x;
  vector.y = y;
  vector.z = z;
  vector.w = 0.0f;

  if (vector.w != 0.0f) {
    printf("vector.w is not 0.0f\n");
    return false;
  }

  if (TupleEqual(&point, &vector)) {
    printf("point and vector are equal\n");
    return false;
  }

  return true;
}

static inline bool TestTupleAdd(float x1, float y1, float z1, float w1,
                                float x2, float y2, float z2, float w2) {
  Tuple left = {};
  left.x = x1;
  left.y = y1;
  left.z = z1;
  left.w = w1;

  Tuple right = {};
  right.x = x2;
  right.y = y2;
  right.z = z2;
  right.w = w2;

  Tuple result = {};
  result = TupleAdd(&left, &right);

  Tuple check = {};
  check.x = x1 + x2;
  check.y = y1 + y2;
  check.z = z1 + z2;
  check.w = w1 + w2;

  if (!TupleEqual(&result, &check)) {
    printf("TupleAdd failed\n");
    return false;
  }

  return true;
}

static inline bool TestTupleSubtract(float x1, float y1, float z1, float w1,
                                     float x2, float y2, float z2, float w2) {
  Tuple left = {};
  left.x = x1;
  left.y = y1;
  left.z = z1;
  left.w = w1;

  Tuple right = {};
  right.x = x2;
  right.y = y2;
  right.z = z2;
  right.w = w2;

  Tuple result = {};
  result = TupleSubtract(&left, &right);

  Tuple check = {};
  check.x = x1 - x2;
  check.y = y1 - y2;
  check.z = z1 - z2;
  check.w = w1 - w2;

  if (!TupleEqual(&result, &check)) {
    printf("TupleAdd failed\n");
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  if (!TestTupleVector(4.3f, -4.2f, 3.1f)) {
    printf("TestTupleVector failed\n");
    return 1;
  }

  if (!TestTupleAdd(3.0f, -2.0f, 5.0f, 1.0f, -2.0f, 3.0f, 1.0f, 0.0f)) {
    printf("TestTupleAdd failed\n");
    return 1;
  }

  if (!TestTupleSubtract(3.0f, 2.0f, 1.0f, 1.0f, -2.0f, 3.0f, 1.0f, 0.0f)) {
    printf("TestTupleAdd failed\n");
    return 1;
  }

  return 0;
}
