#include <src/matrix.h>
#include <src/test_suite.h>

#include <functional>

const char* NORMAL = "\033[0m";
const char* RED = "\33[0;31m";
const char* GREEN = "\33[0;32m";

void TestFramework::AddTest(const char* name,
                            std::function<bool()> test_function) {
  tests[current_test_idx] = {name, test_function};
  current_test_idx++;
}

void TestFramework::RunTest() {
  for (int i = 0; i < current_test_idx; ++i) {
    CustomTest* test = &tests[i];
    printf("%s", test->name);
    total_tests++;
    if (test->test_function()) {
      printf(" %sPASSED%s\n", GREEN, NORMAL);
      passed_tests++;
    } else {
      printf(" %sFAILED%s\n", RED, NORMAL);
    }
  }
  printf("\nTest summary: %d/%d tests passed.\n", passed_tests, total_tests);
}

bool IsEqualFloat(const float a, const float b) {
  return a == b || std::abs(a - b) <= FLT_EPSILON;
}

bool AssertEqInts(const int& actual, const int& expected,
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

bool AssertEqFloats(const float& actual, const float& expected,
                    const char* actual_name, const char* expected_name,
                    const char* file, int line) {
  if (!IsEqualFloat(actual, expected)) {
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

bool AssertEqMatrices(Matrix* actual, Matrix* expected, const char* actual_name,
                      const char* expected_name, const char* file, int line) {
  if (!(*actual == *expected)) {
    printf("\nError: %s:%d: Assertion failed: %s == %s\n", file, line,
           actual_name, expected_name);
    printf("Actual: %s\n", actual->ToString().c_str());
    printf("Expected: %s\n", expected->ToString().c_str());
    fflush(stdout);
    return false;
  }
  return true;
}
