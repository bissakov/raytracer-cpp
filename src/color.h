#ifndef SRC_COLOR_H_
#define SRC_COLOR_H_

#include <immintrin.h>

#include <cstdint>
#include <iostream>
#include <string>

struct Color {
  union {
    __m128 vec;
    struct {
      float r, g, b, a;
    };
  };

  Color() noexcept;
  Color(const float r, const float g, const float b, const float a) noexcept;
  Color(const float r, const float g, const float b) noexcept;
  explicit Color(const __m128 vec) noexcept;
  Color(const Color& other) noexcept;
  Color& operator=(const Color& other) noexcept;

  Color operator+(const Color& other) const noexcept;
  Color operator-(const Color& other) const noexcept;
  Color operator*(const Color& other) const noexcept;

  bool operator==(const Color& other) const noexcept;
  bool operator!=(const Color& other) const noexcept;

  Color operator*(const float scalar) const noexcept;
  Color operator/(const float scalar) const noexcept;

  bool IsColorInRange() const noexcept;
  const char* ToHex() const noexcept;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Color& c);

struct ColorRGB {
  union {
    __m128i vec;
    struct {
      int32_t r;
      int32_t g;
      int32_t b;
      int32_t a;
    };
  };

  ColorRGB() noexcept;
  explicit ColorRGB(const __m128i vec) noexcept;
};

#endif  // SRC_COLOR_H_
