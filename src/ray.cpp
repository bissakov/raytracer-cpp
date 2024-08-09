#include <src/point_vector.h>
#include <src/ray.h>
#include <src/test_suite.h>

#include <string>

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

Point Ray::Position(double t) noexcept {
  return origin + direction * t;
}

SphereIntersects Ray::Intersect(Sphere sphere) noexcept {
  SphereIntersects xs;

  Vector sphere_to_ray = origin - sphere.origin;

  double a = DotProduct(direction, direction);
  double b = 2 * DotProduct(direction, sphere_to_ray);
  double c = DotProduct(sphere_to_ray, sphere_to_ray) - 1;

  double discriminant = (b * b) - (4 * a * c);

  if (discriminant < 0.0) {
    return xs;
  } else if (IsEqualDouble(discriminant, 0.0)) {
    double t = -b / (2 * a);
    xs.Push(t, &sphere);
  } else {
    double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    xs.Push(t1, &sphere);
    xs.Push(t2, &sphere);
  }

  return xs;
}

Sphere& Sphere::operator=(const Sphere& other) noexcept {
  if (this != &other) {
    origin = other.origin;
    radius = other.radius;
  }
  return *this;
}

bool Sphere::operator==(const Sphere& other) const {
  return origin == other.origin && radius == other.radius;
}

bool Sphere::operator!=(const Sphere& other) const {
  return !(*this == other);
}

Sphere::operator std::string() const noexcept {
  return "Sphere{origin=}" + std::string(origin) +
         ", radius=" + std::to_string(radius) + "}";
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
  os << std::string(sphere);
  return os;
}

SphereIntersects& SphereIntersects::operator=(
    const SphereIntersects& other) noexcept {
  if (this != &other) {
    count = other.count;
    intersects[0] = other.intersects[0];
    intersects[1] = other.intersects[1];
  }
  return *this;
}

Intersection<Sphere>& SphereIntersects::operator[](size_t index) noexcept {
  assert(index < count);
  return intersects[index];
}

const Intersection<Sphere>& SphereIntersects::operator[](
    size_t index) const noexcept {
  assert(index < count);
  return intersects[index];
}

bool SphereIntersects::operator==(const SphereIntersects& other) const {
  if (count != other.count) {
    return false;
  }

  for (size_t i = 0; i < count; ++i) {
    if (intersects[i] != other.intersects[i]) {
      return false;
    }
  }

  return true;
}
bool SphereIntersects::operator!=(const SphereIntersects& other) const {
  return !(*this == other);
}

SphereIntersects::operator std::string() const noexcept {
  std::string str =
      "SphereIntersects{count=" + std::to_string(count) + ", intersections={";
  for (size_t i = 0; i < count; ++i) {
    str += std::string(intersects[i]);
    if (i < count - 1) {
      str += ", ";
    }
  }
  str += "}}";
  return str;
}

std::ostream& operator<<(std::ostream& os,
                         const SphereIntersects& intersections) {
  os << std::string(intersections);
  return os;
}

void SphereIntersects::Push(double t, Sphere* sphere) noexcept {
  assert(count + 1 <= 2 && "Ray can't intersect a sphere >2 times...");
  count++;

  Intersection<Sphere> intersect = {t, sphere};
  intersects[count - 1] = intersect;
}
