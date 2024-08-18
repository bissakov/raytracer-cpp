#ifndef SRC_PIXEL_H_
#define SRC_PIXEL_H_

#include <cstdint>
#include <iostream>
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
  const char* ToHex() const;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Color& c);

struct Pixel {
  size_t x;
  size_t y;
  Color color;

  bool operator==(const Pixel& other) const;
  bool operator!=(const Pixel& other) const;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Pixel& p);

struct ColorRGB {
  size_t r = SIZE_MAX;
  size_t g = SIZE_MAX;
  size_t b = SIZE_MAX;
};

#endif  // SRC_PIXEL_H_
