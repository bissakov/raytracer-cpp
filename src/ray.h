#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/arr.h>
#include <src/canvas.h>
#include <src/light.h>
#include <src/material.h>
#include <src/matrix.h>
#include <src/point.h>
#include <src/vector.h>

#include <string>

#define HITS_BUFFER_SIZE 10240

typedef struct Hits Hits;

enum ObjectType { SPHERE = 1 };

struct Sphere {
  Point origin;
  Matrix transform_matrix;
  Material material;
  float radius;

  Sphere() noexcept;
  Sphere(const Point& origin, const Matrix& transform,
         const float radius) noexcept;
  Sphere(const Point& origin, const Matrix& transform, const float radius,
         const Material& material) noexcept;
  explicit Sphere(const Material& material) noexcept;
  Sphere(const Sphere& other) noexcept;
  Sphere& operator=(const Sphere& other) noexcept;

  bool operator==(const Sphere& other) const;
  bool operator!=(const Sphere& other) const;

  Vector NormalAt(const Point& point) noexcept;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Sphere& sphere);

struct Object {
  void* data;
  ObjectType type;

  Object() noexcept;
  Object(void* data, ObjectType type) noexcept;
  Object(const Object& other) noexcept;
  Object& operator=(const Object& other) noexcept;

  bool operator==(const Object& other) const;
  bool operator!=(const Object& other) const;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Object& object);

struct Ray {
  Point origin;
  Vector direction;

  Ray() noexcept {}
  Ray(const Point& origin, const Vector& direction) noexcept;
  Ray(const Ray& other) noexcept;
  Ray& operator=(const Ray& other) noexcept;

  bool operator==(const Ray& other) const;
  bool operator!=(const Ray& other) const;

  Point Position(float t) noexcept;
  Hits Intersect(Sphere sphere) noexcept;
  Ray Transform(Matrix transform) noexcept;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Ray& ray);

struct Hit {
  Object object;
  float t;

  Hit() noexcept;
  Hit(const Object& object, float t) noexcept;
  Hit(const Hit& other) noexcept;
  Hit& operator=(const Hit& other) noexcept;

  bool operator==(const Hit& other) const;
  bool operator!=(const Hit& other) const;
  bool operator<(const Hit& other) const;
  bool operator<=(const Hit& other) const;
  bool operator>(const Hit& other) const;
  bool operator>=(const Hit& other) const;

  operator std::string() const noexcept;
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

  void Push(const Hit& hit) noexcept;
  int32_t FirstHitIdx() noexcept;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hits& hits);

void CastShapeUnshaded(Canvas* canvas, const Point& ray_origin,
                       const Sphere& shape, float wall_z,
                       float wall_size) noexcept;

void CastShapeShaded(Canvas* canvas, const Point& ray_origin,
                     const Sphere& shape, const PointLight& light, float wall_z,
                     float wall_size) noexcept;

#endif  // SRC_RAY_H_
