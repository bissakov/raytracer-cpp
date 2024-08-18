#include <immintrin.h>
#include <src/color.h>
#include <src/test_suite.h>
#include <src/utils.h>

#include <cassert>
#include <cstdio>
#include <format>

Color::Color() noexcept : vec(_mm_set_ps(1.f, 0.f, 0.f, 0.f)) {}

Color::Color(const float r, const float g, const float b,
             const float a) noexcept
    : vec(_mm_set_ps(a, b, g, r)) {}

Color::Color(const float r, const float g, const float b) noexcept
    : vec(_mm_set_ps(1.f, b, g, r)) {}

Color::Color(const __m128 vec) noexcept : vec(vec) {}

Color::Color(const Color& other) noexcept : vec(other.vec) {}

Color& Color::operator=(const Color& other) noexcept {
  if (this != &other) {
    vec = other.vec;
  }
  return *this;
}

Color Color::operator+(const Color& other) const noexcept {
  return Color{_mm_add_ps(vec, other.vec)};
}

Color Color::operator-(const Color& other) const noexcept {
  return Color{_mm_sub_ps(vec, other.vec)};
}

Color Color::operator*(const Color& other) const noexcept {
  return Color{_mm_mul_ps(vec, other.vec)};
}

bool Color::operator==(const Color& other) const noexcept {
  return IsEqualFloat(r, other.r) && IsEqualFloat(g, other.g) &&
         IsEqualFloat(b, other.b);
}

bool Color::operator!=(const Color& other) const noexcept {
  return !(*this == other);
}

Color Color::operator*(const float scalar) const noexcept {
  return Color{_mm_mul_ps(vec, _mm_set1_ps(scalar))};
}

Color Color::operator/(const float scalar) const noexcept {
  return Color{_mm_div_ps(vec, _mm_set1_ps(scalar))};
}

bool Color::IsColorInRange() const noexcept {
  return (r >= 0.0f && r <= 1.0f) && (g >= 0.0f && g <= 1.0f) &&
         (b >= 0.0f && b <= 1.0f);
}

const char* Color::ToHex() const noexcept {
  assert(IsColorInRange() && "Color out of range");

  std::string hex_chars = "0123456789abcdef";
  static char hex[7];

  size_t red = Clamp(static_cast<size_t>(r * 255.0f), 0, 255);
  size_t green = Clamp(static_cast<size_t>(g * 255.0f), 0, 255);
  size_t blue = Clamp(static_cast<size_t>(b * 255.0f), 0, 255);

  hex[0] = hex_chars[static_cast<int>(red / 16)];
  hex[1] = hex_chars[red % 16];
  hex[2] = hex_chars[static_cast<int>(green / 16)];
  hex[3] = hex_chars[green % 16];
  hex[4] = hex_chars[static_cast<int>(blue / 16)];
  hex[5] = hex_chars[blue % 16];
  hex[6] = '\0';

  return hex;
}

Color::operator std::string() const noexcept {
  return std::format("Color(r={:.10f}, g={:.10f}, b={:.10f})", r, g, b);
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
  os << std::string(c);
  return os;
}
