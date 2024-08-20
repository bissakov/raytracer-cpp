#include <core/test_suite.h>
#include <geometry/matrix.h>

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <functional>
#include <string>

#define NORMAL "\033[0m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

constexpr static inline size_t Map(size_t value, size_t src_min, size_t src_max,
                                   size_t dest_min, size_t dest_max) {
  size_t src_range = src_max - src_min;
  size_t dest_range = dest_max - dest_min;
  size_t scaled_value = (value - src_min) * dest_range / src_range;

  return dest_min + scaled_value;
}

static inline std::string GetColor(const std::string& tag) noexcept {
  std::hash<std::string> hash_fn;
  size_t color_code = Map(hash_fn(tag) % 100, 0, 100, 31, 36);
  std::string color = "\033[0;" + std::to_string(color_code) + "m";
  return color;
}

void TestFramework::Summary() const noexcept {
  printf("\nTest summary: %s%s%zu/%zu%s tests passed.\n", UNDERLINE,
         (passed_tests == total_tests) ? GREEN : RED, passed_tests, total_tests,
         NORMAL);
}

void TestFramework::Run(const char* name, const char* tag,
                        std::function<bool()> test_function) noexcept {
  CustomTest test{test_function, tag, name};

  printf("%s%s%s \"%s\"", GetColor(test.tag).c_str(), test.tag, NORMAL,
         test.name);
  total_tests++;

  if (test.test_function()) {
    printf(" %s%sPASSED%s\n", ITALIC, GREEN, NORMAL);
    passed_tests++;
  } else {
    printf(" %s%sFAILED%s\n", ITALIC, RED, NORMAL);
  }
  current_test_idx++;
}

bool IsEqualDouble(const double a, const double b) noexcept {
  return a == b || (std::fabs(a - b) <=
                    std::max(DBL_EPSILON * std::max(std::abs(a), std::abs(b)),
                             ABSOLUTE_TOLERANCE));
}

bool IsEqualFloat(const float a, const float b) noexcept {
  return a == b || (std::fabs(a - b) <= static_cast<float>(ABSOLUTE_TOLERANCE));
}

bool AssertEqFloat(const float& actual, const float& expected,
                   const char* actual_name, const char* expected_name,
                   const char* file, int line) noexcept {
  if (!IsEqualFloat(actual, expected)) {
    std::cerr << "\nError: " << file << ":" << line
              << ":Assertion failed: " << actual_name << " == " << expected_name
              << "\n";
    std::cerr << "Actual: " << actual << "\n";
    std::cerr << "Expected: " << expected << "\n";
    return false;
  }
  return true;
}
