#include <src/pixel.h>
#include <src/test_suite.h>
#include <src/utils.h>

#include <cassert>
#include <cstdio>

Color Color::operator+(const Color& other) const {
  return {r + other.r, g + other.g, b + other.b};
}

Color Color::operator-(const Color& other) const {
  return {r - other.r, g - other.g, b - other.b};
}

Color Color::operator*(const Color& other) const {
  return {r * other.r, g * other.g, b * other.b};
}

bool Color::operator==(const Color& other) const {
  return IsEqualDouble(r, other.r) && IsEqualDouble(g, other.g) &&
         IsEqualDouble(b, other.b);
}

bool Color::operator!=(const Color& other) const {
  return !IsEqualDouble(r, other.r) || !IsEqualDouble(g, other.g) ||
         !IsEqualDouble(b, other.b);
}

Color Color::operator*(const double scalar) const {
  return {r * scalar, g * scalar, b * scalar};
}

Color Color::operator/(const double scalar) const {
  return {r / scalar, g / scalar, b / scalar};
}

bool Color::IsColorInRange() const {
  return (r >= 0.0f && r <= 1.0f) && (g >= 0.0f && g <= 1.0f) &&
         (b >= 0.0f && b <= 1.0f);
}

const char* Color::ToHex() const {
  assert(IsColorInRange() && "Color out of range");

  const char* hex_chars = "0123456789abcdef";
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

Color::operator const char*() const noexcept {
  static char buffer[30];
  snprintf(buffer, sizeof(buffer), "Color{r=%.02f, g=%.02f, b=%.02f}", r, g, b);
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
  os << (const char*)c;
  return os;
}

bool Pixel::operator==(const Pixel& other) const {
  return IsEqualDouble(color.r, other.color.r) &&
         IsEqualDouble(color.g, other.color.g) &&
         IsEqualDouble(color.b, other.color.b);
}
bool Pixel::operator!=(const Pixel& other) const {
  return !IsEqualDouble(color.r, other.color.r) ||
         !IsEqualDouble(color.g, other.color.g) ||
         !IsEqualDouble(color.b, other.color.b);
}

Pixel::operator const char*() const noexcept {
  static char buffer[100];
  snprintf(buffer, sizeof(buffer), "Pixel{x=%zu, y=%zu, color={%f, %f, %f}}", x,
           y, color.r, color.g, color.b);
  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Pixel& p) {
  os << (const char*)p;
  return os;
}
