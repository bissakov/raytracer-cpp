#include <src/main.h>
#include <src/point_vector.h>
#include <src/test_suite.h>

#include <cmath>

int main(int argc, char* argv[]) {
  TestFramework framework;

  framework.AddTest("Point + vector", []() -> bool {
    Point left = {3.0f, -2.0f, 5.0f};
    Vector right = {-2.0f, 3.0f, 1.0f};
    Point expected = {1.0f, 1.0f, 6.0f};
    return AssertEq(left + right, expected);
  });

  framework.AddTest("Point + vector", []() -> bool {
    Point left = {3.0f, -2.0f, 5.0f};
    Vector right = {-2.0f, 3.0f, 1.0f};
    Point expected = {1.0f, 1.0f, 6.0f};
    return AssertEq(left + right, expected);
  });

  framework.AddTest("Point - point", []() -> bool {
    Point left = {3.0f, 2.0f, 1.0f};
    Point right = {-2.0f, 3.0f, 1.0f};
    Vector expected = {5.0f, -1.0f, 0.0f};
    return AssertEq(left - right, expected);
  });

  framework.AddTest("Point - vector", []() -> bool {
    Point left = {3.0f, 2.0f, 1.0f};
    Vector right = {5.0f, 6.0f, 7.0f};
    Point expected = {-2.0f, -4.0f, -6.0f};
    return AssertEq(left - right, expected);
  });

  framework.AddTest("Vector - vector", []() -> bool {
    Vector left = {3.0f, 2.0f, 1.0f};
    Vector right = {5.0f, 6.0f, 7.0f};
    Vector expected = {-2.0f, -4.0f, -6.0f};
    return AssertEq(left - right, expected);
  });

  framework.AddTest("Negate vector", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {-1.0f, 2.0f, -3.0f};
    return AssertEq(-v, expected);
  });

  framework.AddTest("Multiply vector", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {3.5f, -7.0f, 10.5f};
    return AssertEq(v * 3.5f, expected);
  });

  framework.AddTest("Divide vector by multiplying", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {0.5f, -1.0f, 1.5f};
    return AssertEq(v * 0.5f, expected);
  });

  framework.AddTest("Divide vector", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {0.5f, -1.0f, 1.5f};
    return AssertEq(v / 2.0f, expected);
  });

  framework.AddTest("The magnitude of a vector 1", []() -> bool {
    Vector v = {1.0f, 0.0f, 0.0f};
    float expected = 1.0f;
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework.AddTest("The magnitude of a vector 2", []() -> bool {
    Vector v = {0.0f, 1.0f, 0.0f};
    float expected = 1.0f;
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework.AddTest("The magnitude of a vector 3", []() -> bool {
    Vector v = {0.0f, 0.0f, 1.0f};
    float expected = 1.0f;
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework.AddTest("The magnitude of a vector 4", []() -> bool {
    Vector v = {1.0f, 2.0f, 3.0f};
    float expected = sqrt(14.0f);
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework.AddTest("The magnitude of a vector 5", []() -> bool {
    Vector v = {-1.0f, -2.0f, -3.0f};
    float expected = sqrt(14.0f);
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework.AddTest("Normalize vector 1", []() -> bool {
    Vector v = {4.0f, 0.0f, 0.0f};
    Vector expected = {1.0f, 0.0f, 0.0f};
    return AssertEq(v.Normalize(), expected);
  });

  framework.AddTest("Normalize vector 2", []() -> bool {
    Vector v = {1.0f, 2.0f, 3.0f};
    Vector expected = {1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f),
                       3.0f / sqrt(14.0f)};
    return AssertEq(v.Normalize(), expected);
  });

  framework.AddTest("The magnitude of a normalized vector", []() -> bool {
    Vector v = {1.0f, 2.0f, 3.0f};

    Vector nv = v.Normalize();
    float mn = nv.Magnitude();

    float expected = 1.0f;

    return AssertFloatEq(mn, expected);
  });

  framework.RunTest();

  return 0;
}
