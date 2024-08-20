#include <geometry/point.h>
#include <geometry/vector.h>
#include <render/light.h>
#include <render/material.h>

#include <cmath>
#include <format>

PointLight::PointLight() noexcept {}

PointLight::PointLight(const Color &intensity, const Point &position) noexcept
    : intensity(intensity), position(position) {}

PointLight::PointLight(const PointLight &other) noexcept
    : intensity(other.intensity), position(other.position) {}

PointLight &PointLight::operator=(const PointLight &other) noexcept {
  if (this != &other) {
    intensity = other.intensity;
    position = other.position;
  }
  return *this;
}

bool PointLight::operator==(const PointLight &other) const noexcept {
  return intensity == other.intensity && position == other.position;
}

bool PointLight::operator!=(const PointLight &other) const noexcept {
  return !(*this == other);
}

Color Lighting(const Material &material, const PointLight &light,
               const Point &position, const Vector &eye_vector,
               const Vector &normal_vector) noexcept {
  Color effective_color{material.color * light.intensity};
  Vector light_vector{(light.position - position).Normalize()};
  Color ambient_color{effective_color * material.ambient};

  float light_dot_normal = DotProduct(light_vector, normal_vector);

  Color diffuse_color{0, 0, 0};
  Color specular_color{0, 0, 0};

  if (light_dot_normal >= 0.F) {
    diffuse_color = effective_color * material.diffuse * light_dot_normal;

    Vector reflect_vector = -light_vector.Reflect(normal_vector);
    float reflect_dot_eye = DotProduct(reflect_vector, eye_vector);

    if (reflect_dot_eye > 0.F) {
      float factor = std::pow(reflect_dot_eye, material.shininess);
      specular_color = light.intensity * material.specular * factor;
    }
  }

  return ambient_color + diffuse_color + specular_color;
}

PointLight::operator std::string() const noexcept {
  return std::format("PointLight(intensity={}, position={})",
                     std::string(intensity), std::string(position));
}

std::ostream &operator<<(std::ostream &os, const PointLight &point_light) {
  os << std::string(point_light);
  return os;
}
