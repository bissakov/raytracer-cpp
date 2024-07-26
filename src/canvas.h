#ifndef SRC_CANVAS_H_
#define SRC_CANVAS_H_

#include <src/pixel.h>

#include <string>

struct Canvas {
  int width;
  int height;
  Pixel** pixels;

  Canvas(const int _width, const int _height);
  ~Canvas();

  bool IsPixelOutOfBounds(const int pos_x, const int pos_y) const;
  Pixel PixelAt(const int pos_x, const int pos_y) const;
  void WritePixelColor(const int pos_x, const int pos_y,
                       const Color& color) const;
  std::string ToString() const;
};

#endif  // SRC_CANVAS_H_
