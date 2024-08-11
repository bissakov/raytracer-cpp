#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/arr.h>
#include <src/point_vector.h>

typedef struct Sphere Sphere;
typedef struct Hit Hit;
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
  operator const char*() const noexcept;

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

  operator const char*() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Sphere& sphere);

enum ObjectType { SPHERE = 1 };

struct Object {
  void* data;
  ObjectType type;

  Object() noexcept : data(nullptr), type(SPHERE) {}
  Object(void* data, ObjectType type) noexcept : data(data), type(type) {}
  Object(const Object& other) noexcept : data(other.data), type(other.type) {}
  Object& operator=(const Object& other) noexcept;

  bool operator==(const Object& other) const;
  bool operator!=(const Object& other) const;
  operator const char*() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Object& object);

struct Hit {
  Object object;
  double t;

  Hit() noexcept : t(0.0) {}
  Hit(Object object, double t) noexcept : object(object), t(t) {}
  Hit(const Hit& other) noexcept : object(other.object), t(other.t) {}
  Hit& operator=(const Hit& other) noexcept;

  bool operator==(const Hit& other) const;
  bool operator!=(const Hit& other) const;
  operator const char*() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hit& hit);

struct Hits {
  Hit hits[2];
  size_t count;

  Hits() noexcept : count(0) {}
  explicit Hits(size_t count) noexcept : count(count) {}
  Hits(const Hits& other) noexcept : count(other.count) {
    hits[0] = other.hits[0];
    hits[1] = other.hits[1];
  }
  Hits& operator=(const Hits& other) noexcept;

  Hit& operator[](size_t index) noexcept;
  const Hit& operator[](size_t index) const noexcept;

  bool operator==(const Hits& other) const;
  bool operator!=(const Hits& other) const;

  operator const char*() const noexcept;

  void Push(Hit hit) noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hits& hits);

#endif  // SRC_RAY_H_
