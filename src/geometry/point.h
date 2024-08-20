#ifndef SRC_GEOMETRY_POINT_H_
#define SRC_GEOMETRY_POINT_H_

#include <immintrin.h>

#include <iostream>
#include <string>

typedef struct Vector Vector;

struct Point {
  union {
    __m128 vec;
    struct {
      float x, y, z, w;
    };
  };

  Point() noexcept;
  Point(float x, float y, float z) noexcept;
  Point(const Point& other) noexcept;
  explicit Point(__m128 vec) noexcept;
  Point& operator=(const Point& other) noexcept;

  float& operator[](size_t index);
  const float& operator[](size_t index) const;

  Point operator+(const Vector& other) const;
  Point operator-(const Vector& other) const;
  Vector operator-(const Point& other) const;

  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

#endif  // SRC_GEOMETRY_POINT_H_
