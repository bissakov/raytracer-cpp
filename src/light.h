#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

#include <src/material.h>
#include <src/pixel.h>
#include <src/point.h>

struct PointLight {
  Color intensity;
  Point position;

  PointLight() noexcept;
  PointLight(const Color &intensity, const Point &position) noexcept;
  PointLight(const PointLight &other) noexcept;
  PointLight &operator=(const PointLight &other) noexcept;

  bool operator==(const PointLight &other) const noexcept;
  bool operator!=(const PointLight &other) const noexcept;

  operator const char *() const noexcept;
};

std::ostream &operator<<(std::ostream &os, const PointLight &point_light);

Color Lighting(const Material &material, const PointLight &light,
               const Point &position, const Vector &eye_vector,
               const Vector &normal_vector) noexcept;

#endif  // SRC_LIGHT_H_
