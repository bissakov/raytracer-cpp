#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/arr.h>
#include <src/point_vector.h>

#include <string>

typedef struct Sphere Sphere;
typedef struct SphereIntersects SphereIntersects;
typedef struct Intersects Intersects;

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
  SphereIntersects Intersect(Sphere sphere) noexcept;
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
struct Intersection {
  double t;
  T* object;

  Intersection<T>() noexcept : t(0.0), object(nullptr) {}

  Intersection<T>(double t, T* object) noexcept : t(t), object(object) {}

  Intersection<T>(const Intersection<T>& other) noexcept
      : t(other.t), object(other.object) {}

  bool operator==(const Intersection<T>& other) const {
    return t == other.t && object == other.object;
  }

  bool operator!=(const Intersection<T>& other) const {
    return !(*this == other);
  }

  operator std::string() const noexcept {
    return "Intersection{t=" + std::to_string(t) +
           ", object=" + std::string(*object) + "}";
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& os,
                         const Intersection<T>& intersection) {
  os << std::string(intersection);
  return os;
}

struct SphereIntersects {
  size_t count;
  Intersection<Sphere> intersects[2];

  SphereIntersects() noexcept : count(0) {}

  explicit SphereIntersects(size_t count) noexcept : count(count) {}

  SphereIntersects(const SphereIntersects& other) noexcept
      : count(other.count) {
    intersects[0] = other.intersects[0];
    intersects[1] = other.intersects[1];
  }

  SphereIntersects& operator=(const SphereIntersects& other) noexcept;

  Intersection<Sphere>& operator[](size_t index) noexcept;
  const Intersection<Sphere>& operator[](size_t index) const noexcept;

  bool operator==(const SphereIntersects& other) const;
  bool operator!=(const SphereIntersects& other) const;
  operator std::string() const noexcept;

  void Push(double t, Sphere* sphere) noexcept;
};

std::ostream& operator<<(std::ostream& os,
                         const SphereIntersects& sphere_intersects);

#endif  // SRC_RAY_H_
