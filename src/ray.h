#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/arr.h>
#include <src/point_vector.h>

#include <string>

typedef struct Sphere Sphere;
typedef struct SphereHits SphereHits;
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
  SphereHits Intersect(Sphere sphere) noexcept;
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

template <typename T>
struct Hit {
  double t;
  T* object;

  Hit<T>() noexcept : t(0.0), object(nullptr) {}

  Hit<T>(double t, T* object) noexcept : t(t), object(object) {}

  Hit<T>(const Hit<T>& other) noexcept : t(other.t), object(other.object) {}

  bool operator==(const Hit<T>& other) const {
    return t == other.t && object == other.object;
  }

  bool operator!=(const Hit<T>& other) const {
    return !(*this == other);
  }

  operator std::string() const noexcept {
    return "Hit{t=" + std::to_string(t) + ", object=" + std::string(*object) +
           "}";
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Hit<T>& hit) {
  os << std::string(hit);
  return os;
}

struct SphereHits {
  size_t count;
  Hit<Sphere> hits[2];

  SphereHits() noexcept : count(0) {}

  explicit SphereHits(size_t count) noexcept : count(count) {}

  SphereHits(const SphereHits& other) noexcept : count(other.count) {
    hits[0] = other.hits[0];
    hits[1] = other.hits[1];
  }

  SphereHits& operator=(const SphereHits& other) noexcept;

  Hit<Sphere>& operator[](size_t index) noexcept;
  const Hit<Sphere>& operator[](size_t index) const noexcept;

  bool operator==(const SphereHits& other) const;
  bool operator!=(const SphereHits& other) const;
  operator std::string() const noexcept;

  void Push(double t, Sphere* sphere) noexcept;
};

std::ostream& operator<<(std::ostream& os, const SphereHits& sphere_hits);

#endif  // SRC_RAY_H_
