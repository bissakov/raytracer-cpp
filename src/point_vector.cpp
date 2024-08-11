#include <src/point_vector.h>
#include <src/test_suite.h>

#include <cmath>
#include <iostream>

// NOTE: Point methods definitions
double &Point::operator[](size_t index) {
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

const double &Point::operator[](size_t index) const {
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
  return IsEqualDouble(x, other.x) && IsEqualDouble(y, other.y) &&
         IsEqualDouble(z, other.z);
}

bool Point::operator!=(const Point &p) const {
  return !(*this == p);
}

Point::operator const char *() const noexcept {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer), "Point{x=%.2f, y=%.2f, z=%.2f, w=%.2f}", x,
           y, z, w);
  return buffer;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
  os << (const char *)p;
  return os;
}

// NOTE: Vector methods definitions
double &Vector::operator[](size_t index) {
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

const double &Vector::operator[](size_t index) const {
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
  return !(*this == other);
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

double DotProduct(const Vector &left, const Vector &right) {
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

double Vector::DotProduct(const Vector &other) const {
  return ::DotProduct(*this, other);
}

Vector CrossProduct(const Vector &left, const Vector &right) {
  return {left.y * right.z - left.z * right.y,
          left.z * right.x - left.x * right.z,
          left.x * right.y - left.y * right.x};
}

Vector Vector::CrossProduct(const Vector &other) const {
  return ::CrossProduct(*this, other);
}

Vector::operator const char *() const noexcept {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer), "Vector{x=%.2f, y=%.2f, z=%.2f, w=%.2f}", x,
           y, z, w);
  return buffer;
}

std::ostream &operator<<(std::ostream &os, const Vector &v) {
  os << (const char *)v;
  return os;
}
