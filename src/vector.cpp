#include <emmintrin.h>
#include <immintrin.h>
#include <src/test_suite.h>
#include <src/vector.h>

#include <cassert>
#include <cmath>
#include <format>
#include <iostream>
#include <string>

Vector::Vector() noexcept : vec(_mm_setzero_ps()) {}

Vector::Vector(const float x, const float y, const float z) noexcept
    : vec(_mm_set_ps(0, z, y, x)) {}

Vector::Vector(const Vector &other) noexcept : vec(other.vec) {}

Vector::Vector(const __m128 vec) noexcept : vec(vec) {}

Vector &Vector::operator=(const Vector &other) noexcept {
  if (this != &other) {
    vec = other.vec;
  }
  return *this;
}

float &Vector::operator[](const size_t index) {
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

const float &Vector::operator[](const size_t index) const {
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

Vector Vector::operator+(const Vector &other) const {
  return Vector{_mm_add_ps(vec, other.vec)};
}

Vector Vector::operator-(const Vector &other) const {
  return Vector{_mm_sub_ps(vec, other.vec)};
}

Vector Vector::operator*(const float scalar) const {
  return Vector{_mm_mul_ps(vec, _mm_set1_ps(scalar))};
}

Vector Vector::operator/(const float scalar) const {
  return Vector{_mm_div_ps(vec, _mm_set1_ps(scalar))};
}

bool Vector::operator==(const Vector &other) const {
  __m128 diff = _mm_sub_ps(vec, other.vec);
  diff = _mm_andnot_ps(_mm_set1_ps(-0.0), diff);

  __m128 tolerance = _mm_set1_ps(static_cast<float>(ABSOLUTE_TOLERANCE));
  __m128 cmp = _mm_cmp_ps(diff, tolerance, _CMP_LE_OQ);

  return _mm_testc_ps(cmp, _mm_set1_ps(-1.0));
}

bool Vector::operator!=(const Vector &other) const {
  return !(*this == other);
}

Vector Vector::operator-() const {
  return Vector{_mm_mul_ps(vec, _mm_set1_ps(-1))};
}

float Vector::Magnitude() const {
  // TODO(bissakov): use AVX instructions
  return sqrt(x * x + y * y + z * z);
}

Vector Vector::Normalize() const {
  return Vector{_mm_div_ps(vec, _mm_set1_ps(Magnitude()))};
}

float DotProduct(const Vector &left, const Vector &right) {
  Vector res{Vector{_mm_mul_ps(left.vec, right.vec)}};
  return res.x + res.y + res.w + res.z;
}

float Vector::DotProduct(const Vector &other) const {
  return ::DotProduct(*this, other);
}

Vector CrossProduct(const Vector &left, const Vector &right) {
  // TODO(bissakov): use AVX instructions
  return {left.y * right.z - left.z * right.y,
          left.z * right.x - left.x * right.z,
          left.x * right.y - left.y * right.x};
}

Vector Vector::CrossProduct(const Vector &other) const {
  return ::CrossProduct(*this, other);
}

Vector Vector::Reflect(const Vector &normal) const {
  return *this - normal * 2 * DotProduct(normal);
}

Vector::operator std::string() const noexcept {
  return std::format("Vector(x={:.10f}, y={:.10f}, z={:.10f},w={:.10f})", x, y,
                     z, w);
}

std::ostream &operator<<(std::ostream &os, const Vector &v) {
  os << std::string(v);
  return os;
}
