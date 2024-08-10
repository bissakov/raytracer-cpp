#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/arr.h>
#include <src/point_vector.h>

#include <algorithm>
#include <memory>
#include <string>

typedef struct Sphere Sphere;
typedef struct Hits Hits;

struct Ray {
  Point origin;
  Vector direction;

  Ray() noexcept {}
  Ray(Point origin_, Vector direction_) noexcept
      : origin(origin_), direction(direction_) {}
  Ray(const Ray& other) noexcept
      : origin(other.origin), direction(other.direction) {}
  Ray& operator=(const Ray& other) noexcept;

  bool operator==(const Ray& other) const;
  bool operator!=(const Ray& other) const;
  operator std::string() const noexcept;

  Point Position(double t) noexcept;
  Hits Intersect(Sphere sphere) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Ray& ray);

struct Sphere {
  Point origin;
  double radius;

  Sphere() noexcept : origin({0, 0, 0}), radius(1.0) {}
  Sphere(Point origin, double radius) noexcept
      : origin(origin), radius(radius) {}
  Sphere(const Sphere& other) noexcept
      : origin(other.origin), radius(other.radius) {}
  Sphere& operator=(const Sphere& other) noexcept;

  bool operator==(const Sphere& other) const;
  bool operator!=(const Sphere& other) const;
  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Sphere& sphere);

enum ObjectType { SPHERE = 1 };

struct Object {
  ObjectType type;
  void* data;

  Object() noexcept : type(SPHERE), data(nullptr) {}
  Object(ObjectType type, void* data) noexcept : type(type), data(data) {}
  Object(const Object& other) noexcept : type(other.type), data(other.data) {}
  Object& operator=(const Object& other) noexcept;

  bool operator==(const Object& other) const;
  bool operator!=(const Object& other) const;
  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Object& object);

struct Hit {
  double t;
  Object object;

  Hit() noexcept : t(0.0) {}
  Hit(double t, Object object) noexcept : t(t), object(object) {}
  Hit(const Hit& other) noexcept : t(other.t), object(other.object) {}
  Hit& operator=(const Hit& other) noexcept;

  bool operator==(const Hit& other) const;
  bool operator!=(const Hit& other) const;
  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hit& hit);

struct Hits {
  size_t count;
  std::unique_ptr<Hit[]> hits;

  Hits() noexcept : count(0), hits(nullptr) {}
  explicit Hits(size_t count) noexcept
      : count(count), hits(std::make_unique<Hit[]>(count)) {}
  Hits(const Hits& other) noexcept
      : count(other.count), hits(std::make_unique<Hit[]>(count)) {
    std::copy(other.hits.get(), other.hits.get() + count, hits.get());
  }
  Hits& operator=(const Hits& other) noexcept;

  Hit& operator[](size_t index) noexcept;
  const Hit& operator[](size_t index) const noexcept;

  bool operator==(const Hits& other) const;
  bool operator!=(const Hits& other) const;
  operator std::string() const noexcept;

  void Push(double t, Object object) noexcept;
  void Push(Hit* hit) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hits& hits);

Hits Aggregate(size_t size, Hit* hits) noexcept;

#endif  // SRC_RAY_H_
