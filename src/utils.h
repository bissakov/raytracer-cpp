#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <windows.h>

void ErrorExit(LPCTSTR function);

constexpr int Min(int a, int b) {
  return (a < b) ? a : b;
}

constexpr int Max(int a, int b) {
  return (a > b) ? a : b;
}

constexpr int Clamp(int value, int min_value, int max_value) {
  return Max(min_value, Min(value, max_value));
}

#endif  // SRC_UTILS_H_
