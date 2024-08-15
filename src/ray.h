#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/arr.h>
#include <src/canvas.h>
#include <src/material.h>
#include <src/matrix.h>
#include <src/point.h>
#include <src/vector.h>

#define HITS_BUFFER_SIZE 10240

typedef struct Sphere Sphere;
typedef struct Hits Hits;

struct Ray {
  Point origin;
  Vector direction;

  Ray() noexcept {}
  Ray(const Point& origin, const Vector& direction) noexcept;
  Ray(const Ray& other) noexcept;
  Ray& operator=(const Ray& other) noexcept;

  bool operator==(const Ray& other) const;
  bool operator!=(const Ray& other) const;
  operator const char*() const noexcept;

  Point Position(double t) noexcept;
  Hits Intersect(Sphere sphere) noexcept;
  Ray Transform(Matrix transform) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Ray& ray);

struct Sphere {
  Point origin;
  Matrix transform_matrix;
  double radius;
  Material material;

  Sphere() noexcept;
  Sphere(const Point& origin, const Matrix& transform,
         const double radius) noexcept;
  Sphere(const Point& origin, const Matrix& transform, const double radius,
         const Material& material) noexcept;
  explicit Sphere(const Material& material) noexcept;
  Sphere(const Sphere& other) noexcept;
  Sphere& operator=(const Sphere& other) noexcept;

  bool operator==(const Sphere& other) const;
  bool operator!=(const Sphere& other) const;

  operator const char*() const noexcept;

  Vector NormalAt(const Point& point) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Sphere& sphere);

enum ObjectType { SPHERE = 1 };

struct Object {
  void* data;
  ObjectType type;

  Object() noexcept;
  Object(void* data, ObjectType type) noexcept;
  Object(const Object& other) noexcept;
  Object& operator=(const Object& other) noexcept;

  bool operator==(const Object& other) const;
  bool operator!=(const Object& other) const;
  operator const char*() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Object& object);

struct Hit {
  Object object;
  double t;

  Hit() noexcept;
  Hit(const Object& object, double t) noexcept;
  Hit(const Hit& other) noexcept;
  Hit& operator=(const Hit& other) noexcept;

  bool operator==(const Hit& other) const;
  bool operator!=(const Hit& other) const;
  bool operator<(const Hit& other) const;
  bool operator<=(const Hit& other) const;
  bool operator>(const Hit& other) const;
  bool operator>=(const Hit& other) const;

  operator const char*() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hit& hit);

struct Hits {
  DyArray<Hit> hits;
  size_t count;

  Hits() noexcept;
  explicit Hits(size_t count) noexcept;
  Hits(const Hits& other) noexcept;

  Hits(std::initializer_list<Hit> hit_list) noexcept : count(0) {
    for (const auto& hit : hit_list) {
      Push(hit);
    }
  }
  Hits& operator=(const Hits& other) noexcept;

  Hit& operator[](size_t index) noexcept;
  const Hit& operator[](size_t index) const noexcept;

  bool operator==(const Hits& other) const;
  bool operator!=(const Hits& other) const;

  operator const char*() const noexcept;

  void Push(const Hit& hit) noexcept;
  int32_t FirstHitIdx() noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hits& hits);

void CastShape(Canvas* canvas, const Point& ray_origin, const Sphere& shape,
               double wall_z, double wall_size) noexcept;

#endif  // SRC_RAY_H_
