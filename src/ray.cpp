#include <src/point_vector.h>
#include <src/ray.h>
#include <src/test_suite.h>

#include <cstdarg>
#include <memory>
#include <string>
#include <utility>

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

Hits Ray::Intersect(Sphere sphere) noexcept {
  Hits xs;

  Vector sphere_to_ray = origin - sphere.origin;

  double a = DotProduct(direction, direction);
  double b = 2 * DotProduct(direction, sphere_to_ray);
  double c = DotProduct(sphere_to_ray, sphere_to_ray) - 1;

  double discriminant = (b * b) - (4 * a * c);

  Object object = {SPHERE, &sphere};

  if (discriminant < 0.0) {
    return xs;
  } else if (IsEqualDouble(discriminant, 0.0)) {
    double t = -b / (2 * a);

    xs.Push(t, object);
  } else {
    double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

    xs.Push(t1, object);
    xs.Push(t2, object);
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
  return "Sphere{origin=" + std::string(origin) +
         ", radius=" + std::to_string(radius) + "}";
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
  os << std::string(sphere);
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

Object::operator std::string() const noexcept {
  return "Object{type=" + std::to_string(type) + "}";
}

Hit& Hit::operator=(const Hit& other) noexcept {
  if (this != &other) {
    t = other.t;
    object = other.object;
  }
  return *this;
}

bool Hit::operator==(const Hit& other) const {
  return t == other.t && object == other.object;
}

bool Hit::operator!=(const Hit& other) const {
  return !(*this == other);
}

Hit::operator std::string() const noexcept {
  std::string str = "Hit{t=" + std::to_string(t) + ", object_type=";
  switch (object.type) {
    case (1): {
      str += "SPHERE, data=" +
             std::string(*reinterpret_cast<Sphere*>(object.data));
      break;
    }
  }
  return str;
}

std::ostream& operator<<(std::ostream& os, const Hit& hit) {
  os << std::string(hit);
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

Hits::operator std::string() const noexcept {
  std::string str = "Hits{count=" + std::to_string(count) + ", hits={";
  for (size_t i = 0; i < count; ++i) {
    str += std::string(hits[i]);
    if (i < count - 1) {
      str += ", ";
    }
  }
  str += "}}";
  return str;
}

std::ostream& operator<<(std::ostream& os, const Hits& hits) {
  os << std::string(hits);
  return os;
}

void Hits::Push(double t, Object object) noexcept {
  if (count == 0) {
    hits = std::make_unique<Hit[]>(1);
    hits[0] = {t, object};
    count = 1;
  } else {
    auto new_hits = std::make_unique<Hit[]>(count + 1);
    std::copy(hits.get(), hits.get() + count, new_hits.get());
    new_hits[count] = {t, object};
    hits = std::move(new_hits);
    count++;
  }
}

void Hits::Push(Hit* hit) noexcept {
  Push(hit->t, hit->object);
}

Hits Aggregate(size_t size, Hit* hits) noexcept {
  Hits xs;
  for (size_t i = 0; i < size; ++i) {
    Hit* hit = &hits[i];
    xs.Push(hit);
  }
  return xs;
}
