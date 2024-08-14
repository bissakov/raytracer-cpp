#include <src/point.h>
#include <src/test_suite.h>

#include <cassert>

Point::Point() noexcept : x(0.0), y(0.0), z(0.0), w(1.0) {}

Point::Point(const double x, const double y, const double z) noexcept
    : x(x), y(y), z(z), w(1.0) {}

Point::Point(const Point &other) noexcept
    : x(other.x), y(other.y), z(other.z), w(other.w) {}

Point &Point::operator=(const Point &other) noexcept {
  if (this != &other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
  }
  return *this;
}

double &Point::operator[](const size_t index) {
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

const double &Point::operator[](const size_t index) const {
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
