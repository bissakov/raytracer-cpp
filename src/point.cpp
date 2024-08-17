#include <immintrin.h>
#include <src/point.h>
#include <src/test_suite.h>

#include <cassert>
#include <format>

Point::Point() noexcept : vec(_mm256_setzero_pd()) {}

Point::Point(const double x, const double y, const double z) noexcept
    : vec(_mm256_set_pd(1.0, z, y, x)) {}

Point::Point(const Point &other) noexcept : vec(other.vec) {}

Point::Point(const __m256d vec) noexcept : vec(vec) {}

Point &Point::operator=(const Point &other) noexcept {
  if (this != &other) {
    vec = other.vec;
  }
  return *this;
}

double &Point::operator[](const size_t index) {
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

const double &Point::operator[](const size_t index) const {
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
  return Point{_mm256_add_pd(vec, other.vec)};
}

Point Point::operator-(const Vector &other) const {
  return Point{_mm256_sub_pd(vec, other.vec)};
}

Vector Point::operator-(const Point &other) const {
  return Vector{_mm256_sub_pd(vec, other.vec)};
}

bool Point::operator==(const Point &other) const {
  // TODO(bissakov): use AVX instructions
  return IsEqualDouble(x, other.x) && IsEqualDouble(y, other.y) &&
         IsEqualDouble(z, other.z);
}

bool Point::operator!=(const Point &p) const {
  return !(*this == p);
}

Point::operator std::string() const noexcept {
  return std::format("Point(x={:.2f}, y={:.2f}, z={:.2f}, w={:.2f})", x, y, z,
                     w);
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << std::string(p);
  return os;
}
