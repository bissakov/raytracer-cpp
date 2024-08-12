#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/arr.h>
#include <src/point.h>
#include <src/vector.h>

#define HITS_BUFFER_SIZE 10240

typedef struct Sphere Sphere;
typedef struct Hits Hits;

struct Ray {
  Point origin;
  Vector direction;

  Ray() noexcept {}
  Ray(Point origin_, Vector direction_) noexcept;
  Ray(const Ray& other) noexcept;
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

  Sphere() noexcept;
  Sphere(Point origin, double radius) noexcept;
  Sphere(const Sphere& other) noexcept;
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
  Hit(Object object, double t) noexcept;
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

  void Push(Hit hit) noexcept;
  const Hit& FirstHit() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Hits& hits);

#endif  // SRC_RAY_H_
