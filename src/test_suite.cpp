#include <src/matrix.h>
#include <src/test_suite.h>

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <functional>
#include <string>

// NOTE: The lowest passing value so far - 3.553 * 10^-15
#define ABSOLUTE_TOLERANCE 1e-14  // 10^-14

const char* NORMAL = "\033[0m";
const char* ITALIC = "\033[3m";
const char* UNDERLINE = "\033[4m";
const char* RED = "\033[1;31m";
const char* GREEN = "\033[1;32m";

bool CustomTest::operator==(const CustomTest& other) const noexcept {
  return tag == other.tag && name == other.name;
}

bool CustomTest::operator!=(const CustomTest& other) const noexcept {
  return !(*this == other);
}

CustomTest& CustomTest::operator=(const CustomTest& other) noexcept {
  if (this != &other) {
    name = other.name;
    tag = other.tag;
    test_function = other.test_function;
  }
  return *this;
}

void TestFramework::Add(const char* name, const char* tag,
                        std::function<bool()> test_function) {
  CustomTest test = {test_function, tag, name};
  tests.Push(test);
  current_test_idx++;
}

std::string GetColor(size_t idx) {
  size_t start = 31;
  size_t color_idx = (start + idx) % 36;
  if (color_idx < start) {
    color_idx += start;
  }
  std::string color = "\033[0;" + std::to_string(color_idx) + "m";
  return color;
}

void TestFramework::RunTests() {
  size_t current_tag_idx = 0;
  for (size_t i = 0; i < current_test_idx; ++i) {
    CustomTest* test = &(tests.Get(i));

    if (i > 0 && strcmp(test->tag, tests.Get(i - 1).tag) != 0) {
      current_tag_idx++;
    }

    printf("%s%s%s \"%s\"", GetColor(current_tag_idx).c_str(), test->tag,
           NORMAL, test->name);
    total_tests++;
    if (test->test_function()) {
      printf(" %s%sPASSED%s\n", ITALIC, GREEN, NORMAL);
      passed_tests++;
    } else {
      printf(" %s%sFAILED%s\n", ITALIC, RED, NORMAL);
    }
  }

  printf("\nTest summary: %s%s%zu/%zu%s tests passed.\n", UNDERLINE,
         (passed_tests == total_tests) ? GREEN : RED, passed_tests, total_tests,
         NORMAL);
}

bool IsEqualDouble(const double a, const double b) {
  return a == b || (std::fabs(a - b) <=
                    std::max(DBL_EPSILON * std::max(std::abs(a), std::abs(b)),
                             ABSOLUTE_TOLERANCE));
}
