#include <src/light.h>
#include <src/point.h>
#include <src/ray.h>
#include <src/test_suite.h>
#include <src/vector.h>

#include <cstdio>
#include <format>
#include <string>
#include <thread>

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

Point Ray::Position(float t) noexcept {
  return origin + direction * t;
}

Hits Ray::Intersect(Sphere sphere) noexcept {
  Hits hits;

  Ray ray{Transform(sphere.transform_matrix.Inverse())};

  Vector sphere_to_ray{ray.origin - sphere.origin};

  float a = DotProduct(ray.direction, ray.direction);
  float b = 2 * DotProduct(ray.direction, sphere_to_ray);
  float c = DotProduct(sphere_to_ray, sphere_to_ray) - 1;

  float discriminant = (b * b) - (4 * a * c);

  Object object{&sphere, SPHERE};

  if (IsEqualFloat(discriminant, 0.0)) {
    float t = -b / (2 * a);
    hits.Push({object, t});
  } else if (discriminant > 0.0) {
    float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
    float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
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
               const float radius) noexcept
    : origin(origin), transform_matrix(transform), radius(radius) {}

Sphere::Sphere(const Point& origin, const Matrix& transform, const float radius,
               const Material& material) noexcept
    : origin(origin),
      transform_matrix(transform),
      radius(radius),
      material(material) {}

Sphere::Sphere(const Material& material) noexcept : material(material) {}

Sphere::Sphere(const Sphere& other) noexcept
    : origin(other.origin),
      transform_matrix(other.transform_matrix),
      radius(other.radius),
      material(other.material) {}

Sphere& Sphere::operator=(const Sphere& other) noexcept {
  if (this != &other) {
    origin = other.origin;
    transform_matrix = other.transform_matrix;
    radius = other.radius;
    material = other.material;
  }
  return *this;
}

bool Sphere::operator==(const Sphere& other) const {
  return origin == other.origin && transform_matrix == other.transform_matrix &&
         radius == other.radius && material == other.material;
}

bool Sphere::operator!=(const Sphere& other) const {
  return !(*this == other);
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

Hit::Hit() noexcept : t(0.0) {}

Hit::Hit(const Object& object, float t) noexcept : object(object), t(t) {}

Hit::Hit(const Hit& other) noexcept : object(other.object), t(other.t) {}

Hit& Hit::operator=(const Hit& other) noexcept {
  if (this != &other) {
    object = other.object;
    t = other.t;
  }
  return *this;
}

bool Hit::operator==(const Hit& other) const {
  return IsEqualFloat(t, other.t) && object == other.object;
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

struct DrawRegionUnshadedContext {
  const Point& ray_origin;
  const Sphere& shape;
  float wall_z;
  float pixel_size;
  float half_wall_size;
  size_t start;
  size_t end;
};

static inline void DrawRegionUnshaded(
    Canvas* canvas, const DrawRegionUnshadedContext& context) {
  for (size_t y = context.start; y < context.end; ++y) {
    float world_y = context.half_wall_size - context.pixel_size * y;
    for (size_t x = 0; x < canvas->width; ++x) {
      float world_x = -context.half_wall_size + context.pixel_size * x;

      Point position{world_x, world_y, context.wall_z};
      Ray ray{context.ray_origin, (position - context.ray_origin).Normalize()};
      Hits hits{ray.Intersect(context.shape)};

      if (hits.count > 0) {
        canvas->WriteColor(x, y, context.shape.material.color);
      }
    }
  }
}
#define ArraySize(arr) (sizeof(arr) / sizeof((arr)[0]))

void CastShapeUnshaded(Canvas* canvas, const Point& ray_origin,
                       const Sphere& shape, float wall_z,
                       float wall_size) noexcept {
  float pixel_size = wall_size / static_cast<float>(canvas->width);
  float half_wall_size = wall_size / 2;

  std::thread workers[10];
  size_t workers_count = ArraySize(workers);
  size_t chunk_size = canvas->height / workers_count;

  for (size_t worker_idx = 0; worker_idx < workers_count; ++worker_idx) {
    size_t start = chunk_size * worker_idx;
    size_t end =
        (worker_idx == workers_count - 1) ? canvas->height : start + chunk_size;

    DrawRegionUnshadedContext context = {
        ray_origin, shape, wall_z, pixel_size, half_wall_size, start, end};

    workers[worker_idx] = std::thread(DrawRegionUnshaded, canvas, context);
  }

  for (size_t worker_idx = 0; worker_idx < workers_count; ++worker_idx) {
    workers[worker_idx].join();
  }
}

struct DrawRegionShadedContext {
  const Point& ray_origin;
  const Sphere& shape;
  const PointLight& light;
  float wall_z;
  float pixel_size;
  float half_wall_size;
  size_t start;
  size_t end;
};

static inline void DrawRegionShaded(Canvas* canvas,
                                    const DrawRegionShadedContext& context) {
  for (size_t y = context.start; y < context.end; ++y) {
    float world_y = context.half_wall_size - context.pixel_size * y;
    for (size_t x = 0; x < canvas->width; ++x) {
      float world_x = -context.half_wall_size + context.pixel_size * x;

      Point position{world_x, world_y, context.wall_z};
      Ray ray{context.ray_origin, (position - context.ray_origin).Normalize()};
      Hits hits{ray.Intersect(context.shape)};

      if (hits.count > 0) {
        Hit hit{hits[0]};
        Sphere* object = reinterpret_cast<Sphere*>(hit.object.data);

        Point point{ray.Position(hit.t)};
        Vector normal{object->NormalAt(point)};
        Vector eye{-ray.direction};

        Color color =
            Lighting(object->material, context.light, point, eye, normal);
        canvas->WriteColor(x, y, color);
      }
    }
  }
}

void CastShapeShaded(Canvas* canvas, const Point& ray_origin,
                     const Sphere& shape, const PointLight& light, float wall_z,
                     float wall_size) noexcept {
  float pixel_size = wall_size / static_cast<float>(canvas->width);
  float half_wall_size = wall_size / 2;

  std::thread workers[20];
  size_t workers_count = ArraySize(workers);
  size_t chunk_size = canvas->height / workers_count;

  for (size_t worker_idx = 0; worker_idx < workers_count; ++worker_idx) {
    size_t start = chunk_size * worker_idx;
    size_t end =
        (worker_idx == workers_count - 1) ? canvas->height : start + chunk_size;

    DrawRegionShadedContext context = {ray_origin, shape,      light,
                                       wall_z,     pixel_size, half_wall_size,
                                       start,      end};

    workers[worker_idx] = std::thread(DrawRegionShaded, canvas, context);
  }

  for (size_t worker_idx = 0; worker_idx < workers_count; ++worker_idx) {
    workers[worker_idx].join();
  }
}

Ray::operator std::string() const noexcept {
  return std::format("Ray(origin={}, direction={})", std::string(origin),
                     std::string(direction));
}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
  os << std::string(ray);
  return os;
}

Sphere::operator std::string() const noexcept {
  return std::format(
      "Sphere(origin={}, transform={}, radius={:.10f}, material={})",
      std::string(origin), std::string(transform_matrix), radius,
      std::string(material));
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
  os << std::string(sphere);
  return os;
}

Object::operator std::string() const noexcept {
  switch (type) {
    case (1): {
      Sphere sphere = *reinterpret_cast<Sphere*>(data);
      return std::format("Object(type=SPHERE, data={})", std::string(sphere));
    }
    default: {
      return "Object(type=UNKNOWN)";
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Object& object) {
  os << std::string(object);
  return os;
}

Hit::operator std::string() const noexcept {
  return std::format("Hit(t={:.10f}, object={})", t, std::string(object));
}

std::ostream& operator<<(std::ostream& os, const Hit& hit) {
  os << std::string(hit);
  return os;
}

Hits::operator std::string() const noexcept {
  std::string str = std::format("Hits(count={}", count);

  if (count == 0) {
    str += "}";
    return str;
  }

  str += ", ";

  for (size_t i = 0; i < count; ++i) {
    str += std::string(hits[i]);
    if (i < count - 1) {
      str += ", ";
    }
  }

  str += ')';

  return str;
}

std::ostream& operator<<(std::ostream& os, const Hits& hits) {
  os << std::string(hits);
  return os;
}
