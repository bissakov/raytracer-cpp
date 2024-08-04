#ifndef SRC_TEST_SUITE_H_
#define SRC_TEST_SUITE_H_

#include <src/arr.h>
#include <src/matrix.h>
#include <src/pixel.h>
#include <src/point_vector.h>

#include <functional>
#include <string>

struct CustomTest {
  std::function<bool()> test_function;
  const char* tag;
  const char* name;

  CustomTest(const char* name_, const char* tag_,
             std::function<bool()> test_function_) noexcept
      : test_function(test_function_), tag(tag_), name(name_) {}

  CustomTest() noexcept
      : test_function([]() -> bool { return true; }), tag(""), name("") {}

  CustomTest& operator=(const CustomTest& other) noexcept;
  bool operator==(const CustomTest& other) const noexcept;
  bool operator!=(const CustomTest& other) const noexcept;
};

struct TestFramework {
  std::string root;
  DyArray<CustomTest> tests;
  size_t passed_tests = 0;
  size_t total_tests = 0;
  size_t current_test_idx = 0;

  explicit TestFramework(std::string root_) noexcept : root(root_) {}

  void AddTest(const char* name, const char* tag,
               std::function<bool()> test_function);
  void RunTests();
};

bool IsEqualDouble(const double a, const double b);

bool AssertEqInts(const int& actual, const int& expected,
                  const char* actual_name, const char* expected_name,
                  const char* file, int line);

bool AssertEqSizeT(const size_t& actual, const size_t& expected,
                   const char* actual_name, const char* expected_name,
                   const char* file, int line);

bool AssertEqDoubles(const double& actual, const double& expected,
                     const char* actual_name, const char* expected_name,
                     const char* file, int line);

bool AssertEqBools(const bool& actual, const bool& expected,
                   const char* actual_name, const char* expected_name,
                   const char* file, int line);

bool AssertEqPoints(const Point& actual, const Point& expected,
                    const char* actual_name, const char* expected_name,
                    const char* file, int line);

bool AssertEqVectors(const Vector& actual, const Vector& expected,
                     const char* actual_name, const char* expected_name,
                     const char* file, int line);

bool AssertEqColors(const Color& actual, const Color& expected,
                    const char* actual_name, const char* expected_name,
                    const char* file, int line);

bool AssertEqMatrices(const Matrix& actual, const Matrix& expected,
                      const char* actual_name, const char* expected_name,
                      const char* file, int line);

#define ASSERT_EQUAL_INTS(actual, expected) \
  AssertEqInts(actual, expected, #actual, #expected, __FILE__, __LINE__)

#define ASSERT_EQUAL_SIZE_T(actual, expected) \
  AssertEqSizeT(actual, expected, #actual, #expected, __FILE__, __LINE__)

#define ASSERT_EQUAL_DOUBLES(actual, expected) \
  AssertEqDoubles(actual, expected, #actual, #expected, __FILE__, __LINE__)

#define ASSERT_EQUAL_BOOLS(actual, expected) \
  AssertEqBools(actual, expected, #actual, #expected, __FILE__, __LINE__)

#define ASSERT_EQUAL_POINTS(actual, expected) \
  AssertEqPoints(actual, expected, #actual, #expected, __FILE__, __LINE__)

#define ASSERT_EQUAL_VECTORS(actual, expected) \
  AssertEqVectors(actual, expected, #actual, #expected, __FILE__, __LINE__)

#define ASSERT_EQUAL_COLORS(actual, expected) \
  AssertEqColors(actual, expected, #actual, #expected, __FILE__, __LINE__)

#define ASSERT_EQUAL_MATRICES(actual, expected) \
  AssertEqMatrices(actual, expected, #actual, #expected, __FILE__, __LINE__)

#endif  // SRC_TEST_SUITE_H_
