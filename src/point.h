#ifndef SRC_POINT_H_
#define SRC_POINT_H_

#include <iostream>
#include <string>

typedef struct Vector Vector;

struct Point {
  double x;
  double y;
  double z;
  double w;

  Point() noexcept;
  Point(const double x, const double y, const double z) noexcept;
  Point(const Point& other) noexcept;
  Point& operator=(const Point& other) noexcept;

  double& operator[](const size_t index);
  const double& operator[](const size_t index) const;

  Point operator+(const Vector& other) const;
  Point operator-(const Vector& other) const;
  Vector operator-(const Point& other) const;

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

#endif  // SRC_POINT_H_
