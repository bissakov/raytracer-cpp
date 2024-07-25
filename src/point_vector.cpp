#include <src/point_vector.h>

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
  return (x == other.x && y == other.y && z == other.z);
}

bool Vector::operator!=(const Vector &other) const {
  return (x != other.x && y != other.y && z != other.z);
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
