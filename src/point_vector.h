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

  double& operator[](int index) {
    assert(index >= 0 && index <= 3);
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

  const double& operator[](int index) const {
    assert(index >= 0 && index <= 3);
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

  double& operator[](int index) {
    assert(index >= 0 && index <= 3);
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

  const double& operator[](int index) const {
    assert(index >= 0 && index <= 3);
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
