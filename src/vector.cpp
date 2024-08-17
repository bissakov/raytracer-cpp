#include <emmintrin.h>
#include <immintrin.h>
#include <src/test_suite.h>
#include <src/vector.h>

#include <cassert>
#include <cmath>
#include <format>
#include <iostream>
#include <string>

Vector::Vector() noexcept : vec(_mm256_setzero_pd()) {}

Vector::Vector(const double x, const double y, const double z) noexcept
    : vec(_mm256_set_pd(0.0, z, y, x)) {}

Vector::Vector(const Vector &other) noexcept : vec(other.vec) {}

Vector::Vector(const __m256d vec) noexcept : vec(vec) {}

Vector &Vector::operator=(const Vector &other) noexcept {
  if (this != &other) {
    vec = other.vec;
  }
  return *this;
}

double &Vector::operator[](const size_t index) {
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

const double &Vector::operator[](const size_t index) const {
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
  return Vector{_mm256_add_pd(vec, other.vec)};
}

Vector Vector::operator-(const Vector &other) const {
  return Vector{_mm256_sub_pd(vec, other.vec)};
}

Vector Vector::operator*(const double scalar) const {
  return Vector{_mm256_mul_pd(vec, _mm256_set1_pd(scalar))};
}

Vector Vector::operator/(const double scalar) const {
  return Vector{_mm256_div_pd(vec, _mm256_set1_pd(scalar))};
}

bool Vector::operator==(const Vector &other) const {
  // TODO(bissakov): use AVX instructions
  return IsEqualDouble(x, other.x) && IsEqualDouble(y, other.y) &&
         IsEqualDouble(z, other.z);
}

bool Vector::operator!=(const Vector &other) const {
  return !(*this == other);
}

Vector Vector::operator-() const {
  return Vector{_mm256_mul_pd(vec, _mm256_set1_pd(-1))};
}

double Vector::Magnitude() const {
  // TODO(bissakov): use AVX instructions
  return std::sqrt(x * x + y * y + z * z);
}

Vector Vector::Normalize() const {
  return Vector{_mm256_div_pd(vec, _mm256_set1_pd(Magnitude()))};
}

double DotProduct(const Vector &left, const Vector &right) {
  // TODO(bissakov): use AVX instructions
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

double Vector::DotProduct(const Vector &other) const {
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
  return std::format("Vector(x={:.2f}, y={:.2f}, z={:.2f},w={:.2f})", x, y, z,
                     w);
}

std::ostream &operator<<(std::ostream &os, const Vector &v) {
  os << std::string(v);
  return os;
}
