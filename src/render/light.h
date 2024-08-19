#ifndef SRC_RENDER_LIGHT_H_
#define SRC_RENDER_LIGHT_H_

#include <geometry/point.h>
#include <render/color.h>
#include <render/material.h>

#include <string>

struct PointLight {
  Color intensity;
  Point position;

  PointLight() noexcept;
  PointLight(const Color &intensity, const Point &position) noexcept;
  PointLight(const PointLight &other) noexcept;
  PointLight &operator=(const PointLight &other) noexcept;

  bool operator==(const PointLight &other) const noexcept;
  bool operator!=(const PointLight &other) const noexcept;

  operator std::string() const noexcept;
};

std::ostream &operator<<(std::ostream &os, const PointLight &point_light);

Color Lighting(const Material &material, const PointLight &light,
               const Point &position, const Vector &eye_vector,
               const Vector &normal_vector) noexcept;

#endif  // SRC_RENDER_LIGHT_H_
