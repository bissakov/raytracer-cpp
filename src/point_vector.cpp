#include <src/point_vector.h>
#include <src/test_suite.h>

#include <cmath>
#include <string>

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

const std::string Point::ToString() const {
  std::string result = "Point{x=" + std::to_string(x) +
                       ", y=" + std::to_string(y) + ", z=" + std::to_string(z) +
                       "}";
  return result;
}

// NOTE: Vector methods definitions
Vector Vector::operator+(const Vector &other) const {
  return {x + other.x, y + other.y, z + other.z};
}

Vector Vector::operator-(const Vector &other) const {
  return {x - other.x, y - other.y, z - other.z};
}

Vector Vector::operator*(const double scalar) const {
  return {x * scalar, y * scalar, z * scalar};
}

Vector Vector::operator/(const double scalar) const {
  return {x / scalar, y / scalar, z / scalar};
}

bool Vector::operator==(const Vector &other) const {
  return IsEqualDouble(x, other.x) && IsEqualDouble(y, other.y) &&
         IsEqualDouble(z, other.z);
}

bool Vector::operator!=(const Vector &other) const {
  return !IsEqualDouble(x, other.x) || !IsEqualDouble(y, other.y) ||
         !IsEqualDouble(z, other.z);
}

Vector Vector::operator-() const {
  return {-x, -y, -z};
}

double Vector::Magnitude() const {
  return sqrt(x * x + y * y + z * z);
}

Vector Vector::Normalize() const {
  double magnitude = Magnitude();
  return {x / magnitude, y / magnitude, z / magnitude};
}

double Vector::DotProduct(const Vector &other) const {
  return x * other.x + y * other.y + z * other.z;
}

Vector Vector::CrossProduct(const Vector &other) const {
  return {y * other.z - z * other.y, z * other.x - x * other.z,
          x * other.y - y * other.x};
}

double DotProduct(const Vector &left, const Vector &right) {
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector CrossProduct(const Vector &left, const Vector &right) {
  return {left.y * right.z - left.z * right.y,
          left.z * right.x - left.x * right.z,
          left.x * right.y - left.y * right.x};
}

const std::string Vector::ToString() const {
  std::string result = "Vector{x=" + std::to_string(x) +
                       ", y=" + std::to_string(y) + ", z=" + std::to_string(z) +
                       ", w=" + std::to_string(w) + "}";
  return result;
}
