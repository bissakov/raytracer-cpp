#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

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

  float& operator[](const size_t index);
  const float& operator[](const size_t index) const;

  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;

  Vector& operator+=(const Vector& other);
  bool operator==(const Vector& other) const;
  bool operator!=(const Vector& other) const;

  Vector operator*(const float scalar) const;
  Vector operator/(const float scalar) const;

  Vector operator-() const;

  float Magnitude() const;
  Vector Normalize() const;
  float DotProduct(const Vector& other) const;
  Vector CrossProduct(const Vector& other) const;
  Vector Reflect(const Vector& normal) const;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Vector& v);

float DotProduct(const Vector& left, const Vector& right);
Vector CrossProduct(const Vector& left, const Vector& right);

#endif  // SRC_VECTOR_H_
