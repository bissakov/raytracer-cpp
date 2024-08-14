#include <src/point.h>
#include <src/ray.h>
#include <src/test_suite.h>
#include <src/vector.h>

#include <cstdio>

Ray::Ray(const Point& origin, const Vector& direction) noexcept
    : origin(origin), direction(direction) {}

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

  Ray ray{Transform(sphere.transform_matrix.Inverse())};

  Vector sphere_to_ray{ray.origin - sphere.origin};

  double a = DotProduct(ray.direction, ray.direction);
  double b = 2 * DotProduct(ray.direction, sphere_to_ray);
  double c = DotProduct(sphere_to_ray, sphere_to_ray) - 1;

  double discriminant = (b * b) - (4 * a * c);

  Object object{&sphere, SPHERE};

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
  return {transform * origin, transform * direction};
}

Sphere::Sphere() noexcept
    : origin({0, 0, 0}), transform_matrix(Identity()), radius(1.0) {}
Sphere::Sphere(const Point& origin, const Matrix& transform,
               const double radius) noexcept
    : origin(origin), transform_matrix(transform), radius(radius) {}
Sphere::Sphere(const Sphere& other) noexcept
    : origin(other.origin),
      transform_matrix(other.transform_matrix),
      radius(other.radius) {}

Sphere& Sphere::operator=(const Sphere& other) noexcept {
  if (this != &other) {
    origin = other.origin;
    transform_matrix = other.transform_matrix;
    radius = other.radius;
  }
  return *this;
}

bool Sphere::operator==(const Sphere& other) const {
  return origin == other.origin && transform_matrix == other.transform_matrix &&
         radius == other.radius;
}

bool Sphere::operator!=(const Sphere& other) const {
  return !(*this == other);
}

Sphere::operator const char*() const noexcept {
  static char buffer[200];
  snprintf(buffer, sizeof(buffer),
           "Sphere{origin=%s, transform=%s, radius=%.2f}", (const char*)origin,
           (const char*)transform_matrix, radius);
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
  os << (const char*)sphere;
  return os;
}

Vector Sphere::NormalAt(const Point& world_point) noexcept {
  Point object_point{transform_matrix.Inverse() * world_point};
  Vector object_normal{object_point - origin};
  Vector world_normal{
      (transform_matrix.Inverse().Transpose() * object_normal).Normalize()};
  world_normal.w = 0.0;
  return world_normal;
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

Hit::Hit(const Object& object, double t) noexcept : object(object), t(t) {}

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

void Hits::Push(const Hit& hit) noexcept {
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

void CastShape(const Canvas& canvas, const Point& ray_origin,
               const Sphere& shape, const Color& color, double wall_z,
               double wall_size) noexcept {
  double pixel_size = wall_size / static_cast<double>(canvas.width);
  double half_wall_size = wall_size / 2;

  for (size_t y = 0; y < canvas.height; ++y) {
    double world_y = half_wall_size - pixel_size * y;
    for (size_t x = 0; x < canvas.width; ++x) {
      double world_x = -half_wall_size + pixel_size * x;

      Point position{world_x, world_y, wall_z};
      Ray ray{ray_origin, (position - ray_origin).Normalize()};
      Hits hits{ray.Intersect(shape)};

      if (hits.count > 0) {
        canvas.WritePixelColor(x, y, color);
      }
    }
  }
}
