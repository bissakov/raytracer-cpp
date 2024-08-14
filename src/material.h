#ifndef SRC_MATERIAL_H_
#define SRC_MATERIAL_H_

#include <src/pixel.h>

struct Material {
  Color color;
  double ambient;
  double diffuse;
  double specular;
  double shininess;

  Material() noexcept;
  Material(const Color &color, double ambient, double diffuse, double specular,
           double shininess) noexcept;
  Material(const Material &other) noexcept;
  Material &operator=(const Material &other) noexcept;

  bool operator==(const Material &other) const noexcept;
  bool operator!=(const Material &other) const noexcept;

  operator const char *() const noexcept;
};

std::ostream &operator<<(std::ostream &os, const Material &material);

#endif  // SRC_MATERIAL_H_
