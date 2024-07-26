#include <src/pixel.h>
#include <src/test_suite.h>

#include <cassert>
#include <cstdio>
#include <string>

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
  return IsEqualFloat(r, other.r) && IsEqualFloat(g, other.g) &&
         IsEqualFloat(b, other.b);
}

bool Color::operator!=(const Color& other) const {
  return !IsEqualFloat(r, other.r) || !IsEqualFloat(g, other.g) ||
         !IsEqualFloat(b, other.b);
}

Color Color::operator*(const float scalar) const {
  return {r * scalar, g * scalar, b * scalar};
}

Color Color::operator/(const float scalar) const {
  return {r / scalar, g / scalar, b / scalar};
}

bool Color::IsColorInRange() const {
  return (r >= 0.0f && r <= 1.0f) && (g >= 0.0f && g <= 1.0f) &&
         (b >= 0.0f && b <= 1.0f);
}

std::string Color::ToHex() const {
  assert(IsColorInRange() && "Color out of range");

  const char* hex_chars = "0123456789abcdef";
  std::string hex(6, '0');

  int red = static_cast<int>(r * 255.0f);
  int green = static_cast<int>(g * 255.0f);
  int blue = static_cast<int>(b * 255.0f);

  hex[0] = hex_chars[static_cast<int>(red / 16)];
  hex[1] = hex_chars[red % 16];
  hex[2] = hex_chars[static_cast<int>(green / 16)];
  hex[3] = hex_chars[green % 16];
  hex[4] = hex_chars[static_cast<int>(blue / 16)];
  hex[5] = hex_chars[blue % 16];

  return hex;
}

std::string Color::ToString() const {
  char color_buffer[30];
  snprintf(color_buffer, sizeof(color_buffer),
           "Color{r=%.02f, g=%.02f, b=%.02f}", r, g, b);
  std::string color_str = color_buffer;
  return color_str;
}

bool Pixel::operator==(const Pixel& other) const {
  return IsEqualFloat(color.r, other.color.r) &&
         IsEqualFloat(color.g, other.color.g) &&
         IsEqualFloat(color.b, other.color.b);
}
bool Pixel::operator!=(const Pixel& other) const {
  return !IsEqualFloat(color.r, other.color.r) ||
         !IsEqualFloat(color.g, other.color.g) ||
         !IsEqualFloat(color.b, other.color.b);
}

std::string Pixel::ToString() const {
  char color_buffer[100];
  snprintf(color_buffer, sizeof(color_buffer), "Pixel{x=%d, y=%d, color=%s}", x,
           y, color.ToString().c_str());
  std::string color_str = color_buffer;
  return color_str;
}
