#include <src/material.h>
#include <src/test_suite.h>

#include <format>

Material::Material() noexcept
    : color({1, 1, 1}),
      ambient(.1f),
      diffuse(.9f),
      specular(.9f),
      shininess(200.f) {}

Material::Material(const Color &color, float ambient, float diffuse,
                   float specular, float shininess) noexcept
    : color(color),
      ambient(ambient),
      diffuse(diffuse),
      specular(specular),
      shininess(shininess) {}

Material::Material(const Material &other) noexcept
    : color(other.color),
      ambient(other.ambient),
      diffuse(other.diffuse),
      specular(other.specular),
      shininess(other.shininess) {}

Material &Material::operator=(const Material &other) noexcept {
  if (this != &other) {
    color = other.color;
    ambient = other.ambient;
    diffuse = other.diffuse;
    specular = other.specular;
    shininess = other.shininess;
  }
  return *this;
}

bool Material::operator==(const Material &other) const noexcept {
  return color == other.color && IsEqualFloat(ambient, other.ambient) &&
         IsEqualFloat(diffuse, other.diffuse) &&
         IsEqualFloat(specular, other.specular) &&
         IsEqualFloat(shininess, other.shininess);
}

bool Material::operator!=(const Material &other) const noexcept {
  return !(*this == other);
}

Material::operator std::string() const noexcept {
  return std::format(
      "Material(color={}, ambient={:.10f}, diffuse={:.10f}, specular={:.10f}, "
      "shininess={:.10f})",
      std::string(color), ambient, diffuse, specular, shininess);
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
  os << std::string(material);
  return os;
}
