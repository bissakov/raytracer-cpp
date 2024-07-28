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

  operator const char*() const;

  const char* ToString() const;
};

struct Vector {
  float x;
  float y;
  float z;

  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;

  bool operator==(const Vector& other) const;
  bool operator!=(const Vector& other) const;

  Vector operator*(const float scalar) const;
  Vector operator/(const float scalar) const;

  Vector operator-() const;

  float Magnitude() const;
  Vector Normalize() const;
  float DotProduct(const Vector& other) const;
  Vector CrossProduct(const Vector& other) const;

  operator const char*() const;
  const char* ToString() const;
};

float DotProduct(const Vector& left, const Vector& right);
Vector CrossProduct(const Vector& left, const Vector& right);

#endif  // SRC_POINT_VECTOR_H_
