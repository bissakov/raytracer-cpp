#ifndef SRC_TEST_SUITE_H_
#define SRC_TEST_SUITE_H_

#include <src/matrix.h>
#include <src/pixel.h>
#include <src/point_vector.h>

#include <functional>
#include <string>

struct CustomTest {
  const char* name;
  std::function<bool()> test_function;
};

struct TestFramework {
  CustomTest tests[200];
  int passed_tests = 0;
  int total_tests = 0;
  int current_test_idx = 0;
  std::string root_folder_path;

  void AddTest(const char* name, std::function<bool()> test_function);
  void RunTest();
};

bool IsEqualFloat(const float a, const float b);
bool AssertFloatEq(const float a, const float b);

bool AssertEqInts(const int& actual, const int& expected,
                  const char* actual_name, const char* expected_name,
                  const char* file, int line);

bool AssertEqFloats(const float& actual, const float& expected,
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

#define ASSERT_EQUAL_FLOATS(actual, expected) \
  AssertEqFloats(actual, expected, #actual, #expected, __FILE__, __LINE__)

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
