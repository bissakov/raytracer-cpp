#include <src/light.h>
#include <src/material.h>

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

PointLight::operator const char *() const noexcept {
  static char buffer[200];
  snprintf(buffer, sizeof(buffer), "PointLight{intensity=%s, position=%s}",
           (const char *)intensity, (const char *)position);
  return buffer;
}

std::ostream &operator<<(std::ostream &os, const PointLight &point_light) {
  os << (const char *)point_light;
  return os;
}
