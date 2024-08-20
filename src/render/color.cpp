#include <core/test_suite.h>
#include <core/utils.h>
#include <immintrin.h>
#include <render/color.h>
#include <windef.h>

#include <cassert>
#include <format>

Color::Color() noexcept : vec(_mm_set_ps(1.F, 0.F, 0.F, 0.F)) {}

Color::Color(const float r, const float g, const float b,
             const float a) noexcept
    : vec(_mm_set_ps(a, b, g, r)) {}

Color::Color(const float r, const float g, const float b) noexcept
    : vec(_mm_set_ps(1.F, b, g, r)) {}

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
  __m128 lower_bound = _mm_set1_ps(0.F);
  __m128 upper_bound = _mm_set1_ps(1.F);

  __m128 cmp = _mm_and_ps(_mm_cmpge_ps(vec, lower_bound),
                          _mm_cmple_ps(vec, upper_bound));

  return _mm_movemask_ps(cmp) == 0xF;
}

const char* Color::ToHex() const noexcept {
  assert(IsColorInRange() && "Color out of range");

  const char* hex_chars = "0123456789abcdef";
  static char hex[7];

  ColorRGB rgb{NormalizedToRGB(*this)};

  hex[0] = hex_chars[static_cast<int32_t>(rgb.r / 16)];
  hex[1] = hex_chars[rgb.r % 16];
  hex[2] = hex_chars[static_cast<int32_t>(rgb.g / 16)];
  hex[3] = hex_chars[rgb.g % 16];
  hex[4] = hex_chars[static_cast<int32_t>(rgb.b / 16)];
  hex[5] = hex_chars[rgb.b % 16];
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

ColorRGB::ColorRGB() noexcept
    : r(INT_MAX), g(INT_MAX), b(INT_MAX), a(INT_MAX) {}
ColorRGB::ColorRGB(const __m128i vec) noexcept : vec(vec) {}

ColorRGB NormalizedToRGB(const Color& color) noexcept {
  __m128 color_vec = _mm_set_ps(0.F, color.b, color.g, color.r);
  color_vec = _mm_mul_ps(color_vec, _mm_set1_ps(255.F));
  color_vec = _mm_max_ps(color_vec, _mm_set1_ps(0));
  color_vec = _mm_min_ps(color_vec, _mm_set1_ps(255));

  __m128i i32_vec = _mm_cvtps_epi32(color_vec);
  ColorRGB rgb{i32_vec};
  return rgb;
}
