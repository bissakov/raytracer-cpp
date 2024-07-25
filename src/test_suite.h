#ifndef SRC_TEST_SUITE_H_
#define SRC_TEST_SUITE_H_

#include <cstdio>
#include <functional>

struct CustomTest {
  const char* name;
  std::function<bool()> test_function;
};

struct TestFramework {
  CustomTest tests[100];
  int passed_tests = 0;
  int total_tests = 0;
  int current_test_idx = 0;

  void AddTest(const char* name, std::function<bool()> test_function);
  void RunTest();
};

template <typename T>
constexpr bool AssertEq(T a, T b) {
  if (a != b) {
    printf(" Error: Assertion failed");
    fflush(stdout);
    return false;
  }
  return true;
}

bool AssertFloatEq(float a, float b);

#endif  // SRC_TEST_SUITE_H_
