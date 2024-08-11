#include <src/point_vector.h>
#include <src/ray.h>
#include <src/test_suite.h>

#include <cstdio>

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

Ray::operator const char*() const noexcept {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer), "Ray{origin=%s, direction=%s}",
           (const char*)origin, (const char*)direction);
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
  os << (const char*)ray;
  return os;
}

Point Ray::Position(double t) noexcept {
  return origin + direction * t;
}

Hits Ray::Intersect(Sphere sphere) noexcept {
  Hits hits;

  Vector sphere_to_ray = origin - sphere.origin;

  double a = DotProduct(direction, direction);
  double b = 2 * DotProduct(direction, sphere_to_ray);
  double c = DotProduct(sphere_to_ray, sphere_to_ray) - 1;

  double discriminant = (b * b) - (4 * a * c);

  Object object = {&sphere, SPHERE};

  if (IsEqualDouble(discriminant, 0.0)) {
    double t = -b / (2 * a);
    hits.Push({object, t});
  } else if (discriminant > 0.0) {
    double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    hits.Push({object, t1});
    hits.Push({object, t2});
  }

  return hits;
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

Sphere::operator const char*() const noexcept {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer), "Sphere{origin=%s, radius=%.2f}",
           (const char*)origin, radius);
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
  os << (const char*)sphere;
  return os;
}

Object& Object::operator=(const Object& other) noexcept {
  if (this != &other) {
    type = other.type;
    data = other.data;
  }
  return *this;
}

bool Object::operator==(const Object& other) const {
  return type == other.type && data == other.data;
}

bool Object::operator!=(const Object& other) const {
  return !(*this == other);
}

Object::operator const char*() const noexcept {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer), "Object{type=%d}", type);
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Object& object) {
  os << (const char*)object;
  return os;
}

Hit& Hit::operator=(const Hit& other) noexcept {
  if (this != &other) {
    t = other.t;
    object = other.object;
  }
  return *this;
}

bool Hit::operator==(const Hit& other) const {
  return IsEqualDouble(t, other.t) && object == other.object;
}

bool Hit::operator!=(const Hit& other) const {
  return !(*this == other);
}

Hit::operator const char*() const noexcept {
  static char buffer[200];
  snprintf(buffer, sizeof(buffer), "Hit{t=%.2f, object=%s}", t,
           (const char*)object);
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Hit& hit) {
  os << (const char*)hit;
  return os;
}

Hits& Hits::operator=(const Hits& other) noexcept {
  if (this != &other) {
    count = other.count;
    hits[0] = other.hits[0];
    hits[1] = other.hits[1];
  }
  return *this;
}

Hit& Hits::operator[](size_t index) noexcept {
  assert(index < count);
  return hits[index];
}

const Hit& Hits::operator[](size_t index) const noexcept {
  assert(index < count);
  return hits[index];
}

bool Hits::operator==(const Hits& other) const {
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

bool Hits::operator!=(const Hits& other) const {
  return !(*this == other);
}

Hits::operator const char*() const noexcept {
  static char buffer[100];

  switch (count) {
    case 0: {
      snprintf(buffer, sizeof(buffer), "Hits{count=%zu}", count);
    }

    case 1: {
      snprintf(buffer, sizeof(buffer), "Hits{hit=%s, count=%zu}",
               (const char*)hits[0], count);
    }

    case 2: {
      snprintf(buffer, sizeof(buffer), "Hits{hit0=%s, hit1=%s, count=%zu}",
               (const char*)hits[0], (const char*)hits[1], count);
    }

    default: {
      assert("Wrong number of intersections...");
    }
  }

  return buffer;
}

void Hits::Push(Hit hit) noexcept {
  assert(count <= 2);
  hits[count] = hit;
  count++;
}

std::ostream& operator<<(std::ostream& os, const Hits& hits) {
  os << (const char*)hits;
  return os;
}
