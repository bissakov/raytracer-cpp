#include <src/point_vector.h>
#include <src/test_suite.h>

#include <cmath>

// NOTE: Point methods definitions
Point Point::operator+(const Vector &other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Point Point::operator-(const Vector &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Vector Point::operator-(const Point &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

bool Point::operator==(const Point &other) const {
  return (x == other.x && y == other.y && z == other.z);
}

bool Point::operator!=(const Point &p) const {
  return (x != p.x && y != p.y && z != p.z);
}

Point::operator const char *() const {
  return ToString();
}

const char *Point::ToString() const {
  return "Point{x=%.02f, y=%.02.f, z=%.02.f}";
}

// NOTE: Vector methods definitions
Vector Vector::operator+(const Vector &other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Vector Vector::operator-(const Vector &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Vector Vector::operator*(const float scalar) const {
  return {x * scalar, y * scalar, z * scalar};
}

Vector Vector::operator/(const float scalar) const {
  return {x / scalar, y / scalar, z / scalar};
}

bool Vector::operator==(const Vector &other) const {
  return IsEqualFloat(x, other.x) && IsEqualFloat(y, other.y) &&
         IsEqualFloat(z, other.z);
}

bool Vector::operator!=(const Vector &other) const {
  return !IsEqualFloat(x, other.x) || !IsEqualFloat(y, other.y) ||
         !IsEqualFloat(z, other.z);
}

Vector Vector::operator-() const {
  return {-x, -y, -z};
}

float Vector::Magnitude() const {
  return sqrt(x * x + y * y + z * z);
}

Vector Vector::Normalize() const {
  float magnitude = Magnitude();
  return {x / magnitude, y / magnitude, z / magnitude};
}

float Vector::DotProduct(const Vector &other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vector Vector::CrossProduct(const Vector &other) const {
  return {y * other.z - z * other.y, z * other.x - x * other.z,
          x * other.y - y * other.x};
}

float DotProduct(const Vector &left, const Vector &right) {
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector CrossProduct(const Vector &left, const Vector &right) {
  return {left.y * right.z - left.z * right.y,
          left.z * right.x - left.x * right.z,
          left.x * right.y - left.y * right.x};
}

const char *Vector::ToString() const {
  return "Vector{x=%.02f, y=%.02.f, z=%.02.f}";
}

Vector::operator const char *() const {
  return ToString();
}
