#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <windows.h>

void ErrorExit(const LPCTSTR function);

constexpr size_t Min(const size_t a, const size_t b) {
  return (a < b) ? a : b;
}

constexpr size_t Max(const size_t a, const size_t b) {
  return (a > b) ? a : b;
}

constexpr size_t Clamp(const size_t value, const size_t min_value,
                       const size_t max_value) {
  return Max(min_value, Min(value, max_value));
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, min_value, max_value) \
  (MAX(min_value, MIN(value, max_value)))

#endif  // SRC_UTILS_H_
