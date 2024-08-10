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

SphereHits Ray::Intersect(Sphere sphere) noexcept {
  SphereHits xs;

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

SphereHits& SphereHits::operator=(const SphereHits& other) noexcept {
  if (this != &other) {
    count = other.count;
    hits[0] = other.hits[0];
    hits[1] = other.hits[1];
  }
  return *this;
}

Hit<Sphere>& SphereHits::operator[](size_t index) noexcept {
  assert(index < count);
  return hits[index];
}

const Hit<Sphere>& SphereHits::operator[](size_t index) const noexcept {
  assert(index < count);
  return hits[index];
}

bool SphereHits::operator==(const SphereHits& other) const {
  if (count != other.count) {
    return false;
  }

  for (size_t i = 0; i < count; ++i) {
    if (hits[i] != other.hits[i]) {
      return false;
    }
  }

  return true;
}
bool SphereHits::operator!=(const SphereHits& other) const {
  return !(*this == other);
}

SphereHits::operator std::string() const noexcept {
  std::string str = "SphereHits{count=" + std::to_string(count) + ", hits={";
  for (size_t i = 0; i < count; ++i) {
    str += std::string(hits[i]);
    if (i < count - 1) {
      str += ", ";
    }
  }
  str += "}}";
  return str;
}

std::ostream& operator<<(std::ostream& os, const SphereHits& sphere_hits) {
  os << std::string(sphere_hits);
  return os;
}

void SphereHits::Push(double t, Sphere* sphere) noexcept {
  assert(count + 1 <= 2 && "Ray can't intersect a sphere >2 times...");
  count++;

  Hit<Sphere> hit = {t, sphere};
  hits[count - 1] = hit;
}
