#ifndef SRC_POINT_VECTOR_H_
#define SRC_POINT_VECTOR_H_

#include <cassert>
#include <string>

typedef struct Point Point;
typedef struct Vector Vector;

struct Point {
  float x;
  float y;
  float z;
  float w = 1.0f;

  float& operator[](int index) {
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

  const float& operator[](int index) const {
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
  float x;
  float y;
  float z;
  float w = 0.0f;

  float& operator[](int index) {
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

  const float& operator[](int index) const {
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

  Vector operator*(const float scalar) const;
  Vector operator/(const float scalar) const;

  Vector operator-() const;

  float Magnitude() const;
  Vector Normalize() const;
  float DotProduct(const Vector& other) const;
  Vector CrossProduct(const Vector& other) const;

  const std::string ToString() const;
};

float DotProduct(const Vector& left, const Vector& right);
Vector CrossProduct(const Vector& left, const Vector& right);

#endif  // SRC_POINT_VECTOR_H_
