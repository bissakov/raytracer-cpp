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

bool AssertFloatEq(float a, float b) {
  bool is_equal = a == b;
  bool is_equal_eps = std::abs(a - b) <= FLT_EPSILON;
  if (!(is_equal || is_equal_eps)) {
    printf(" Error: Assertion failed");
    fflush(stdout);
    return false;
  }
  return true;
}
