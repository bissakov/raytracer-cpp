#ifndef SRC_RENDER_CANVAS_H_
#define SRC_RENDER_CANVAS_H_

#include <core/utils.h>
#include <render/color.h>

#include <cassert>
#include <memory>
#include <string>

struct Canvas {
  size_t width;
  size_t height;
  std::unique_ptr<Color[]> colors;

  Canvas() noexcept;
  Canvas(size_t width, size_t height) noexcept;
  Canvas(const Canvas &other) noexcept;
  Canvas &operator=(const Canvas &other) noexcept;

  constexpr bool IsInRange(size_t pos_x, size_t pos_y) const noexcept;
  Color ColorAt(size_t pos_x, size_t pos_y) const noexcept;
  void WriteColor(size_t pos_x, size_t pos_y,
                  const Color &color) const noexcept;
  bool SaveToPPM(const Path &file_path) const noexcept;
  bool LoadFromPPM(const Path &file_path) noexcept;

  operator std::string() const noexcept;
};

std::ostream &operator<<(std::ostream &os, const Canvas &c);

constexpr bool Canvas::IsInRange(const size_t pos_x,
                                 const size_t pos_y) const noexcept {
  return (pos_x < width) && (pos_y < height);
}

#endif  // SRC_RENDER_CANVAS_H_
