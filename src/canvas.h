#ifndef SRC_CANVAS_H_
#define SRC_CANVAS_H_

#include <src/pixel.h>

#include <cassert>
#include <string>

struct Canvas {
  int width;
  int height;
  Pixel **pixels;

  Canvas(const int _width, const int _height);
  ~Canvas();

  bool IsPixelOutOfBounds(const int pos_x, const int pos_y) const;
  Pixel PixelAt(const int pos_x, const int pos_y) const;
  void WritePixelColor(const int pos_x, const int pos_y,
                       const Color &color) const;
  std::string ToString() const;
  bool SaveToPPM(std::string file_path);
  bool LoadFromPPM(std::string file_path);
};

static inline void AdvanceUntil(char *file_content, uint32_t *idx,
                                const char terminator);
static inline int StringToInt(char *start, int length);

template <typename T>
T *GetElement(T *elements, int length, int idx) {
  assert(idx >= 0);
  assert(idx < length);
  T *element = &elements[idx];
  return element;
}

#endif  // SRC_CANVAS_H_
