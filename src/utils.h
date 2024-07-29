#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <windows.h>

void ErrorExit(const LPCTSTR function);

constexpr int Min(const int a, const int b) {
  return (a < b) ? a : b;
}

constexpr int Max(const int a, const int b) {
  return (a > b) ? a : b;
}

constexpr int Clamp(const int value, const int min_value, const int max_value) {
  return Max(min_value, Min(value, max_value));
}

#endif  // SRC_UTILS_H_
