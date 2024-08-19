#include <core/test_suite.h>
#include <geometry/vector.h>
#include <immintrin.h>

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

float &Vector::operator[](const size_t index) noexcept {
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

const float &Vector::operator[](const size_t index) const noexcept {
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

bool Vector::operator==(const Vector &other) const noexcept {
  __m128 diff = _mm_sub_ps(vec, other.vec);
  diff = _mm_andnot_ps(_mm_set1_ps(-0.0), diff);

  __m128 tolerance = _mm_set1_ps(static_cast<float>(ABSOLUTE_TOLERANCE));
  __m128 cmp = _mm_cmp_ps(diff, tolerance, _CMP_LE_OQ);

  return _mm_testc_ps(cmp, _mm_set1_ps(-1.0));
}

bool Vector::operator!=(const Vector &other) const noexcept {
  return !(*this == other);
}

Vector Vector::operator+(const Vector &other) const noexcept {
  return Vector{_mm_add_ps(vec, other.vec)};
}

Vector Vector::operator-(const Vector &other) const noexcept {
  return Vector{_mm_sub_ps(vec, other.vec)};
}

Vector Vector::operator*(const float scalar) const noexcept {
  return Vector{_mm_mul_ps(vec, _mm_set1_ps(scalar))};
}

Vector Vector::operator/(const float scalar) const noexcept {
  return Vector{_mm_div_ps(vec, _mm_set1_ps(scalar))};
}

Vector Vector::operator-() const noexcept {
  return Vector{_mm_mul_ps(vec, _mm_set1_ps(-1))};
}

float Vector::Magnitude() const noexcept {
  return sqrt(x * x + y * y + z * z);
}

Vector Vector::Normalize() const noexcept {
  return Vector{_mm_div_ps(vec, _mm_set1_ps(Magnitude()))};
}

float DotProduct(const Vector &left, const Vector &right) noexcept {
  Vector res{Vector{_mm_mul_ps(left.vec, right.vec)}};
  return res.x + res.y + res.w + res.z;
}

float Vector::DotProduct(const Vector &other) const noexcept {
  return ::DotProduct(*this, other);
}

Vector CrossProduct(const Vector &left, const Vector &right) noexcept {
  __m128 left1 = _mm_set_ps(0.f, left.x, left.z, left.y);
  __m128 left2 = _mm_set_ps(0.f, left.y, left.x, left.z);
  __m128 right1 = _mm_set_ps(0.f, right.x, right.z, right.y);
  __m128 right2 = _mm_set_ps(0.f, right.y, right.x, right.z);

  return Vector{
      _mm_sub_ps(_mm_mul_ps(left1, right2), _mm_mul_ps(left2, right1))};
}

Vector Vector::CrossProduct(const Vector &other) const noexcept {
  return ::CrossProduct(*this, other);
}

Vector Vector::Reflect(const Vector &normal) const noexcept {
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
