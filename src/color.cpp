#include <src/color.h>
#include <src/test_suite.h>

Color Color::operator+(const Color& other) const {
  return {red + other.red, green + other.green, blue + other.blue};
}

Color Color::operator-(const Color& other) const {
  return {red - other.red, green - other.green, blue - other.blue};
}
Color Color::operator*(const Color& other) const {
  return {red * other.red, green * other.green, blue * other.blue};
}

bool Color::operator==(const Color& other) const {
  return IsEqualFloat(red, other.red) && IsEqualFloat(green, other.green) &&
         IsEqualFloat(blue, other.blue);
}

bool Color::operator!=(const Color& other) const {
  return !IsEqualFloat(red, other.red) || !IsEqualFloat(green, other.green) ||
         !IsEqualFloat(blue, other.blue);
}

Color Color::operator*(const float scalar) const {
  return {red * scalar, green * scalar, blue * scalar};
}
Color Color::operator/(const float scalar) const {
  return {red / scalar, green / scalar, blue / scalar};
}
