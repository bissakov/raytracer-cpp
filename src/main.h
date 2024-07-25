#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

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
};

struct Vector {
  float x;
  float y;
  float z;

  Vector operator+(const Vector& other) const;
  Vector operator-(const Vector& other) const;
  Vector operator-() const;
  bool operator==(const Vector& other) const;
  bool operator!=(const Vector& other) const;
};

#endif  // SRC_MAIN_H_
