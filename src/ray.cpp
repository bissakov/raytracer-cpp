#include <src/point.h>
#include <src/ray.h>
#include <src/test_suite.h>
#include <src/vector.h>

#include <cstdio>

Ray::Ray(Point origin_, Vector direction_) noexcept
    : origin(origin_), direction(direction_) {}

Ray::Ray(const Ray& other) noexcept
    : origin(other.origin), direction(other.direction) {}

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

Ray Ray::Transform(Matrix transform) noexcept {
  Ray ray = {transform * origin, transform * direction};
  return ray;
}

Sphere::Sphere() noexcept : origin({0, 0, 0}), radius(1.0) {}
Sphere::Sphere(Point origin, double radius) noexcept
    : origin(origin), radius(radius) {}
Sphere::Sphere(const Sphere& other) noexcept
    : origin(other.origin), radius(other.radius) {}

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

Object::Object() noexcept : data(nullptr), type(SPHERE) {}
Object::Object(void* data, ObjectType type) noexcept : data(data), type(type) {}
Object::Object(const Object& other) noexcept
    : data(other.data), type(other.type) {}

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

  switch (type) {
    case (1): {
      snprintf(buffer, sizeof(buffer), "Object{type=SPHERE, data=%s}",
               (const char*)(*reinterpret_cast<Sphere*>(data)));
      break;
    }
  }
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Object& object) {
  os << (const char*)object;
  return os;
}

Hit::Hit() noexcept : t(0.0) {}

Hit::Hit(Object object, double t) noexcept : object(object), t(t) {}

Hit::Hit(const Hit& other) noexcept : object(other.object), t(other.t) {}

Hit& Hit::operator=(const Hit& other) noexcept {
  if (this != &other) {
    object = other.object;
    t = other.t;
  }
  return *this;
}

bool Hit::operator==(const Hit& other) const {
  return IsEqualDouble(t, other.t) && object == other.object;
}

bool Hit::operator!=(const Hit& other) const {
  return !(*this == other);
}

bool Hit::operator<(const Hit& other) const {
  return t < other.t;
}

bool Hit::operator<=(const Hit& other) const {
  return t <= other.t;
}

bool Hit::operator>(const Hit& other) const {
  return t > other.t;
}

bool Hit::operator>=(const Hit& other) const {
  return t >= other.t;
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

Hits::Hits() noexcept : count(0) {}

Hits::Hits(size_t count) noexcept : hits(DyArray<Hit>(count)), count(count) {}

Hits::Hits(const Hits& other) noexcept : hits(other.hits), count(other.count) {}

Hits& Hits::operator=(const Hits& other) noexcept {
  if (this != &other) {
    hits = other.hits;
    count = other.count;
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
  static char buffer[HITS_BUFFER_SIZE];

  if (count == 0) {
    snprintf(buffer, sizeof(buffer), "Hits{count=%zu}", count);
    return buffer;
  }

  size_t buffer_pos =
      snprintf(buffer, sizeof(buffer), "Hits{count=%zu, ", count);

  for (size_t i = 0; i < count; ++i) {
    int written = snprintf(buffer + buffer_pos, HITS_BUFFER_SIZE - buffer_pos,
                           "%s", (const char*)hits[i]);
    buffer_pos += written;

    if (i < count - 1) {
      buffer[buffer_pos++] = ',';
      buffer[buffer_pos++] = ' ';
    }
  }

  buffer[buffer_pos++] = '}';
  buffer[buffer_pos] = '\0';

  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Hits& hits) {
  os << (const char*)hits;
  return os;
}

void Hits::Push(Hit hit) noexcept {
  if (count == 0) {
    hits.Push(hit);
    count++;
    return;
  }

  size_t idx = 0;
  while (idx < count && hits[idx] < hit) {
    idx++;
  }

  hits.Insert(idx, hit);
  count++;
}

int32_t Hits::FirstHitIdx() noexcept {
  assert(count > 0);

  for (int32_t i = 0; i < count; i++) {
    if (hits[i].t >= 0.0) {
      return i;
    }
  }

  return -1;
}
