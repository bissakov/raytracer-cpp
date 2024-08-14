#ifndef SRC_TEST_SUITE_H_
#define SRC_TEST_SUITE_H_

#include <src/arr.h>
#include <src/matrix.h>
#include <src/pixel.h>
#include <src/point.h>
#include <src/vector.h>

#include <functional>

struct CustomTest {
  std::function<bool()> test_function;
  const char* tag;
  const char* name;

  CustomTest(std::function<bool()> test_function, const char* tag,
             const char* name) noexcept
      : test_function(test_function), tag(tag), name(name) {}

  CustomTest() noexcept : test_function([]() -> bool { return true; }) {}
};

struct TestFramework {
  const char* root;
  size_t passed_tests = 0;
  size_t total_tests = 0;
  size_t current_test_idx = 0;

  explicit TestFramework(const char* root_) noexcept : root(root_) {}

  void Run(const char* name, const char* tag,
           std::function<bool()> test_function) noexcept;
  void Summary() noexcept;
};

bool IsEqualDouble(const double a, const double b) noexcept;

template <typename T>
bool AssertEq(const T& actual, const T& expected, const char* actual_name,
              const char* expected_name, const char* file, int line) noexcept {
  if (!(actual == expected)) {
    std::cerr << "\nError: " << file << ":" << line
              << ":Assertion failed: " << actual_name << " == " << expected_name
              << "\n";
    std::cerr << "Actual: " << actual << "\n";
    std::cerr << "Expected: " << expected << "\n";
    return false;
  }
  return true;
}

#define ASSERT_EQUAL(type, actual, expected) \
  AssertEq<type>(actual, expected, #actual, #expected, __FILE__, __LINE__)

#endif  // SRC_TEST_SUITE_H_
