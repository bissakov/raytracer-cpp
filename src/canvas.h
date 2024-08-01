#ifndef SRC_CANVAS_H_
#define SRC_CANVAS_H_

#include <src/pixel.h>

#include <cassert>
#include <string>

struct Canvas {
  size_t width;
  size_t height;
  Pixel *pixels;

  Canvas(const size_t _width, const size_t _height);
  Canvas(const Canvas &other);
  ~Canvas();

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
