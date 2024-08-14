#include <src/material.h>
#include <src/test_suite.h>

Material::Material() noexcept
    : color({1, 1, 1}), ambient(0), diffuse(0), specular(0), shininess(0) {}

Material::Material(const Color &color, double ambient, double diffuse,
                   double specular, double shininess) noexcept
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
  return color == other.color && IsEqualDouble(ambient, other.ambient) &&
         IsEqualDouble(diffuse, other.diffuse) &&
         IsEqualDouble(specular, other.specular) &&
         IsEqualDouble(shininess, other.shininess);
}

bool Material::operator!=(const Material &other) const noexcept {
  return !(*this == other);
}

Material::operator const char *() const noexcept {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer),
           "Material{color=%s, ambient=%.2f, diffuse=%.2f, specular=%.2f, "
           "shininess=%.2f}",
           (const char *)color, ambient, diffuse, specular, shininess);
  return buffer;
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
  os << (const char *)material;
  return os;
}
