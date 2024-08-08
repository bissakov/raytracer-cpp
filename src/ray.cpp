#include <src/ray.h>

Ray& Ray::operator=(const Ray& other) noexcept {
  if (this != &other) {
    origin = other.origin;
    direction = other.direction;
  }
  return *this;
}

bool Ray::operator==(const Ray& other) const {
  return origin == other.origin && direction == other.direction;
}

bool Ray::operator!=(const Ray& other) const {
  return !(*this == other);
}

Ray::operator std::string() const noexcept {
  return "Ray{origin=" + std::string(origin) +
         ", direction=" + std::string(direction) + "}";
}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
  os << std::string(ray);
  return os;
}
