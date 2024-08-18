#ifndef SRC_MATERIAL_H_
#define SRC_MATERIAL_H_

#include <src/color.h>

#include <string>

struct Material {
  Color color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;

  Material() noexcept;
  Material(const Color &color, float ambient, float diffuse, float specular,
           float shininess) noexcept;
  Material(const Material &other) noexcept;
  Material &operator=(const Material &other) noexcept;

  bool operator==(const Material &other) const noexcept;
  bool operator!=(const Material &other) const noexcept;

  operator std::string() const noexcept;
};

std::ostream &operator<<(std::ostream &os, const Material &material);

#endif  // SRC_MATERIAL_H_
