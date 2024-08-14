#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

#include <iostream>

typedef struct Point Point;

struct Vector {
  double x;
  double y;
  double z;
  double w;

  Vector() noexcept;
  Vector(const double x, const double y, const double z) noexcept;
  Vector(const Vector& other) noexcept;
  Vector& operator=(const Vector& other) noexcept;

  double& operator[](const size_t index);
  const double& operator[](const size_t index) const;

  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;

  Vector& operator+=(const Vector& other);
  bool operator==(const Vector& other) const;
  bool operator!=(const Vector& other) const;

  Vector operator*(const double scalar) const;
  Vector operator/(const double scalar) const;

  Vector operator-() const;

  double Magnitude() const;
  Vector Normalize() const;
  double DotProduct(const Vector& other) const;
  Vector CrossProduct(const Vector& other) const;
  Vector Reflect(const Vector& normal) const;

  operator const char*() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Vector& v);

double DotProduct(const Vector& left, const Vector& right);
Vector CrossProduct(const Vector& left, const Vector& right);

#endif  // SRC_VECTOR_H_
