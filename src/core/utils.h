#ifndef SRC_CORE_UTILS_H_
#define SRC_CORE_UTILS_H_

#include <windows.h>

#include <cassert>

void ErrorExit(const LPCTSTR function);

struct Path {
  size_t length;
  char value[MAX_PATH];
};

Path Join(const char* left, const char* right) noexcept;

constexpr size_t Min(const size_t a, const size_t b) {
  return (a < b) ? a : b;
}

constexpr size_t Max(const size_t a, const size_t b) {
  return (a > b) ? a : b;
}

constexpr size_t Map(size_t value, size_t src_min, size_t src_max,
                     size_t dest_min, size_t dest_max) {
  size_t src_range = src_max - src_min;
  size_t dest_range = dest_max - dest_min;
  size_t scaled_value = (value - src_min) * dest_range / src_range;

  return dest_min + scaled_value;
}

constexpr size_t Clamp(const size_t value, const size_t min_value,
                       const size_t max_value) {
  return Max(min_value, Min(value, max_value));
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, min_value, max_value) \
  (MAX(min_value, MIN(value, max_value)))

#endif  // SRC_CORE_UTILS_H_
