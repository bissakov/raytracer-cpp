#ifndef SRC_POINT_VECTOR_H_
#define SRC_POINT_VECTOR_H_

#include <cassert>
#include <string>

typedef struct Point Point;
typedef struct Vector Vector;

struct Point {
  double x;
  double y;
  double z;
  double w = 1.0;

  Point() noexcept : x(0.0), y(0.0), z(0.0), w(1.0) {}
  Point(const double x_, const double y_, const double z_) noexcept
      : x(x_), y(y_), z(z_) {}
  Point(const Point& other) noexcept
      : x(other.x), y(other.y), z(other.z), w(other.w) {}

  double& operator[](size_t index);
  const double& operator[](size_t index) const;

  Point operator+(const Vector& other) const;
  Point operator-(const Vector& other) const;
  Vector operator-(const Point& other) const;

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;

  const std::string ToString() const;
};

struct Vector {
  double x;
  double y;
  double z;
  double w = 0.0;

  Vector() noexcept : x(0.0), y(0.0), z(0.0) {}
  Vector(const double x_, const double y_, const double z_) noexcept
      : x(x_), y(y_), z(z_) {}
  Vector(const Vector& other) noexcept
      : x(other.x), y(other.y), z(other.z), w(other.w) {}

  double& operator[](size_t index);
  const double& operator[](size_t index) const;

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

  const std::string ToString() const;
};

double DotProduct(const Vector& left, const Vector& right);
Vector CrossProduct(const Vector& left, const Vector& right);

#endif  // SRC_POINT_VECTOR_H_
