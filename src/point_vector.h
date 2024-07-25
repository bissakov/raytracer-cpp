#ifndef SRC_POINT_VECTOR_H_
#define SRC_POINT_VECTOR_H_

typedef struct Point Point;
typedef struct Vector Vector;

struct Point {
  float x;
  float y;
  float z;

  Point operator+(const Vector& other) const;
  Point operator-(const Vector& other) const;
  Vector operator-(const Point& other) const;
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;

  const char* ToString() const;
};

struct Vector {
  float x;
  float y;
  float z;

  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;
  Vector operator-() const;
  Vector operator*(const float scalar) const;
  Vector operator/(const float scalar) const;
  bool operator==(const Vector& other) const;
  bool operator!=(const Vector& other) const;

  const char* ToString() const;

  float Magnitude() const;
  Vector Normalize() const;
};

#endif  // SRC_POINT_VECTOR_H_
