#ifndef SRC_PIXEL_H_
#define SRC_PIXEL_H_

#include <string>

struct Color {
  float r;
  float g;
  float b;

  Color operator+(const Color& other) const;
  Color operator-(const Color& other) const;
  Color operator*(const Color& other) const;

  bool operator==(const Color& other) const;
  bool operator!=(const Color& other) const;

  Color operator*(const float scalar) const;
  Color operator/(const float scalar) const;

  bool IsColorInRange() const;
  std::string ToHex() const;
  std::string ToString() const;
};

struct Pixel {
  int x;
  int y;
  Color color;

  bool operator==(const Pixel& other) const;
  bool operator!=(const Pixel& other) const;
  std::string ToString() const;
};

struct ColorRGB {
  int r = -1;
  int g = -1;
  int b = -1;
};

#endif  // SRC_PIXEL_H_
