#ifndef SRC_TEST_SUITE_H_
#define SRC_TEST_SUITE_H_

#include <cstdio>
#include <functional>
#include <string>

struct CustomTest {
  const char* name;
  std::function<bool()> test_function;
};

struct TestFramework {
  CustomTest tests[100];
  int passed_tests = 0;
  int total_tests = 0;
  int current_test_idx = 0;
  std::string root_folder_path;

  void AddTest(const char* name, std::function<bool()> test_function);
  void RunTest();
};

template <typename T>
constexpr bool AssertEq(const T& a, const T& b) {
  if (!(a == b)) {
    printf("Error: Assertion failed\n");
    fflush(stdout);
    return false;
  }
  return true;
}

bool IsEqualFloat(const float a, const float b);
bool AssertFloatEq(const float a, const float b);

#endif  // SRC_TEST_SUITE_H_
