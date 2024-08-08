#ifndef SRC_CANVAS_H_
#define SRC_CANVAS_H_

#include <src/pixel.h>

#include <algorithm>
#include <cassert>
#include <memory>
#include <string>

struct Canvas {
  size_t width;
  size_t height;
  std::unique_ptr<Pixel[]> pixels;

  Canvas() noexcept : width(0), height(0), pixels(nullptr) {}

  Canvas(const size_t width_, const size_t height_) noexcept
      : width(width_),
        height(height_),
        pixels(std::make_unique<Pixel[]>(width_ * height_)) {
    for (size_t row = 0; row < height; ++row) {
      for (size_t col = 0; col < width; ++col) {
        Pixel *pixel = &pixels[row * width + col];
        pixel->x = col;
        pixel->y = row;
        pixel->color = {};
      }
    }
  }

  Canvas(const Canvas &other) noexcept
      : width(other.width),
        height(other.height),
        pixels(std::make_unique<Pixel[]>(other.width * other.height)) {
    std::copy(other.pixels.get(),
              other.pixels.get() + other.width * other.height, pixels.get());
  }

  Canvas &operator=(const Canvas &other);

  bool IsPixelInRange(const size_t pos_x, const size_t pos_y) const;
  Pixel PixelAt(const size_t pos_x, const size_t pos_y) const;
  void WritePixelColor(const size_t pos_x, const size_t pos_y,
                       const Color &color) const;
  std::string ToString() const;
  bool SaveToPPM(const std::string file_path);
  bool LoadFromPPM(const std::string file_path);
};

static inline void AdvanceUntil(char *file_content, uint32_t *idx,
                                const char terminator);
static inline size_t StringToInt(char *start, const size_t length);
static inline bool IsDigit(const char c);

template <typename T>
static inline T *GetElement(T *elements, const size_t length,
                            const size_t idx) {
  assert(idx >= 0);
  assert(idx < length);
  T *element = &elements[idx];
  return element;
}

#endif  // SRC_CANVAS_H_
