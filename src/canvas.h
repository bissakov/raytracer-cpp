#ifndef SRC_CANVAS_H_
#define SRC_CANVAS_H_

#include <src/pixel.h>
#include <src/utils.h>

#include <cassert>
#include <memory>

struct Canvas {
  size_t width;
  size_t height;
  std::unique_ptr<Pixel[]> pixels;

  Canvas() noexcept;
  Canvas(const size_t width_, const size_t height_) noexcept;
  Canvas(const Canvas &other) noexcept;
  Canvas &operator=(const Canvas &other) noexcept;

  constexpr bool IsPixelInRange(const size_t pos_x,
                                const size_t pos_y) const noexcept;
  Pixel PixelAt(const size_t pos_x, const size_t pos_y) const noexcept;
  void WritePixelColor(const size_t pos_x, const size_t pos_y,
                       const Color &color) const noexcept;
  bool SaveToPPM(const Path &file_path) noexcept;
  bool LoadFromPPM(const Path &file_path) noexcept;
};

constexpr bool Canvas::IsPixelInRange(const size_t pos_x,
                                      const size_t pos_y) const noexcept {
  return (pos_x < width) && (pos_y < height);
}

#endif  // SRC_CANVAS_H_
