#include <core/test_suite.h>
#include <geometry/point.h>
#include <immintrin.h>

#include <cassert>
#include <format>

Point::Point() noexcept : vec(_mm_set_ps(1, 0, 0, 0)) {}

Point::Point(const float x, const float y, const float z) noexcept
    : vec(_mm_set_ps(1, z, y, x)) {}

Point::Point(const Point &other) noexcept : vec(other.vec) {}

Point::Point(const __m128 vec) noexcept : vec(vec) {}

Point &Point::operator=(const Point &other) noexcept {
  if (this != &other) {
    vec = other.vec;
  }
  return *this;
}

float &Point::operator[](const size_t index) {
  assert(index < 4);
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      return w;
  }
}

const float &Point::operator[](const size_t index) const {
  assert(index < 4);
  switch (index) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      return w;
  }
}

Point Point::operator+(const Vector &other) const {
  return Point{_mm_add_ps(vec, other.vec)};
}

Point Point::operator-(const Vector &other) const {
  return Point{_mm_sub_ps(vec, other.vec)};
}

Vector Point::operator-(const Point &other) const {
  return Vector{_mm_sub_ps(vec, other.vec)};
}

bool Point::operator==(const Point &other) const {
  __m128 diff = _mm_sub_ps(vec, other.vec);
  diff = _mm_andnot_ps(_mm_set1_ps(-0.0), diff);

  __m128 tolerance = _mm_set1_ps(static_cast<float>(ABSOLUTE_TOLERANCE));
  __m128 cmp = _mm_cmp_ps(diff, tolerance, _CMP_LE_OQ);

  return _mm_testc_ps(cmp, _mm_set1_ps(-1.0));
}

bool Point::operator!=(const Point &p) const {
  return !(*this == p);
}

Point::operator std::string() const noexcept {
  return std::format("Point(x={:.10f}, y={:.10f}, z={:.10f}, w={:.10f})", x, y,
                     z, w);
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << std::string(p);
  return os;
}
