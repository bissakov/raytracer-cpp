#ifndef SRC_GEOMETRY_VECTOR_H_
#define SRC_GEOMETRY_VECTOR_H_

#include <immintrin.h>

#include <iostream>
#include <string>

typedef struct Point Point;

struct Vector {
  union {
    __m128 vec;
    struct {
      float x, y, z, w;
    };
  };

  Vector() noexcept;
  Vector(const float x, const float y, const float z) noexcept;
  Vector(const Vector& other) noexcept;
  explicit Vector(const __m128 vec) noexcept;
  Vector& operator=(const Vector& other) noexcept;

  float& operator[](const size_t index) noexcept;
  const float& operator[](const size_t index) const noexcept;

  bool operator==(const Vector& other) const noexcept;
  bool operator!=(const Vector& other) const noexcept;

  Vector operator+(const Vector& other) const noexcept;
  Vector operator-(const Vector& other) const noexcept;
  Vector operator*(const float scalar) const noexcept;
  Vector operator/(const float scalar) const noexcept;
  Vector operator-() const noexcept;

  float Magnitude() const noexcept;
  Vector Normalize() const noexcept;
  float DotProduct(const Vector& other) const noexcept;
  Vector CrossProduct(const Vector& other) const noexcept;
  Vector Reflect(const Vector& normal) const noexcept;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Vector& v);

float DotProduct(const Vector& left, const Vector& right) noexcept;
Vector CrossProduct(const Vector& left, const Vector& right) noexcept;

#endif  // SRC_GEOMETRY_VECTOR_H_
