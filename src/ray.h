#ifndef SRC_RAY_H_
#define SRC_RAY_H_

#include <src/point_vector.h>

#include <string>

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
};

std::ostream& operator<<(std::ostream& os, const Ray& ray);

#endif  // SRC_RAY_H_
