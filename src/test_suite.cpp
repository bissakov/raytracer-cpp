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
const char* RED = "\033[0;31m";
const char* GREEN = "\033[0;32m";

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

void TestFramework::AddTest(const char* name, const char* tag,
                            std::function<bool()> test_function) {
  tests.Push({name, tag, test_function});
  current_test_idx++;
}

// FIXME: Wrong value wrapping
std::string GetColor(size_t idx) {
  size_t color_idx = (33 + idx) % 36;
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

    printf("%s%s%s %s", GetColor(current_tag_idx).c_str(), test->tag, NORMAL,
           test->name);
    total_tests++;
    if (test->test_function()) {
      printf(" %sPASSED%s\n", GREEN, NORMAL);
      passed_tests++;
    } else {
      printf(" %sFAILED%s\n", RED, NORMAL);
    }
  }

  printf("\nTest summary: %s%zu/%zu%s tests passed.\n",
         (passed_tests == total_tests) ? GREEN : RED, passed_tests, total_tests,
         NORMAL);
}

bool IsEqualDouble(const double a, const double b) {
  return a == b || (std::fabs(a - b) <=
                    std::max(DBL_EPSILON * std::max(std::abs(a), std::abs(b)),
                             ABSOLUTE_TOLERANCE));
}

bool AssertEqSizeT(const size_t& actual, const size_t& expected,
                   const char* actual_name, const char* expected_name,
                   const char* file, int line) {
  if (!(actual == expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %zu\n", actual);
    printf("Expected: %zu\n", expected);
    fflush(stdout);
    return false;
  }
  return true;
}

bool AssertEqSizet(const int& actual, const int& expected,
                   const char* actual_name, const char* expected_name,
                   const char* file, int line);

bool AssertEqDoubles(const double& actual, const double& expected,
                     const char* actual_name, const char* expected_name,
                     const char* file, int line) {
  if (!IsEqualDouble(actual, expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %f\n", actual);
    printf("Expected: %f\n", expected);
    fflush(stdout);
    return false;
  }
  return true;
}

bool AssertEqBools(const bool& actual, const bool& expected,
                   const char* actual_name, const char* expected_name,
                   const char* file, int line) {
  if (!(actual == expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %d\n", actual);
    printf("Expected: %d\n", expected);
    fflush(stdout);
    return false;
  }
  return true;
}

bool AssertEqPoints(const Point& actual, const Point& expected,
                    const char* actual_name, const char* expected_name,
                    const char* file, int line) {
  if (!(actual == expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %s\n", actual.ToString().c_str());
    printf("Expected: %s\n", expected.ToString().c_str());
    fflush(stdout);
    return false;
  }
  return true;
}

bool AssertEqVectors(const Vector& actual, const Vector& expected,
                     const char* actual_name, const char* expected_name,
                     const char* file, int line) {
  if (!(actual == expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %s\n", actual.ToString().c_str());
    printf("Expected: %s\n", expected.ToString().c_str());
    fflush(stdout);
    return false;
  }
  return true;
}

bool AssertEqColors(const Color& actual, const Color& expected,
                    const char* actual_name, const char* expected_name,
                    const char* file, int line) {
  if (!(actual == expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %s\n", actual.ToString().c_str());
    printf("Expected: %s\n", expected.ToString().c_str());
    fflush(stdout);
    return false;
  }
  return true;
}

bool AssertEqMatrices(const Matrix& actual, const Matrix& expected,
                      const char* actual_name, const char* expected_name,
                      const char* file, int line) {
  if (!(actual == expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %s\n", actual.ToString().c_str());
    printf("Expected: %s\n", expected.ToString().c_str());
    fflush(stdout);
    return false;
  }
  return true;
}
