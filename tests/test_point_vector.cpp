#include <src/point_vector.h>
#include <src/test_suite.h>
#include <tests/test_point_vector.h>

#include <cmath>

void TestPointVector(TestFramework *framework) {
  framework->AddTest("Adding point to vector", []() -> bool {
    Point left = {3.0f, -2.0f, 5.0f};
    Vector right = {-2.0f, 3.0f, 1.0f};
    Point expected = {1.0f, 1.0f, 6.0f};
    return AssertEq(left + right, expected);
  });

  framework->AddTest("Subtracting point from point", []() -> bool {
    Point left = {3.0f, 2.0f, 1.0f};
    Point right = {-2.0f, 3.0f, 1.0f};
    Vector expected = {5.0f, -1.0f, 0.0f};
    return AssertEq(left - right, expected);
  });

  framework->AddTest("Subtracting vector from point", []() -> bool {
    Point left = {3.0f, 2.0f, 1.0f};
    Vector right = {5.0f, 6.0f, 7.0f};
    Point expected = {-2.0f, -4.0f, -6.0f};
    return AssertEq(left - right, expected);
  });

  framework->AddTest("Subtracting vector from vector", []() -> bool {
    Vector left = {3.0f, 2.0f, 1.0f};
    Vector right = {5.0f, 6.0f, 7.0f};
    Vector expected = {-2.0f, -4.0f, -6.0f};
    return AssertEq(left - right, expected);
  });

  framework->AddTest("Negate vector", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {-1.0f, 2.0f, -3.0f};
    return AssertEq(-v, expected);
  });

  framework->AddTest("Multiply vector by scalar", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {3.5f, -7.0f, 10.5f};
    return AssertEq(v * 3.5f, expected);
  });

  framework->AddTest("Divide vector by multiplying by scalar", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {0.5f, -1.0f, 1.5f};
    return AssertEq(v * 0.5f, expected);
  });

  framework->AddTest("Divide vector by scalar", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {0.5f, -1.0f, 1.5f};
    return AssertEq(v / 2.0f, expected);
  });

  framework->AddTest("The magnitude of a vector 1", []() -> bool {
    Vector v = {1.0f, 0.0f, 0.0f};
    float expected = 1.0f;
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework->AddTest("The magnitude of a vector 2", []() -> bool {
    Vector v = {0.0f, 1.0f, 0.0f};
    float expected = 1.0f;
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework->AddTest("The magnitude of a vector 3", []() -> bool {
    Vector v = {0.0f, 0.0f, 1.0f};
    float expected = 1.0f;
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework->AddTest("The magnitude of a vector 4", []() -> bool {
    Vector v = {1.0f, 2.0f, 3.0f};
    float expected = sqrt(14.0f);
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework->AddTest("The magnitude of a vector 5", []() -> bool {
    Vector v = {-1.0f, -2.0f, -3.0f};
    float expected = sqrt(14.0f);
    return AssertFloatEq(v.Magnitude(), expected);
  });

  framework->AddTest("Normalize vector 1", []() -> bool {
    Vector v = {4.0f, 0.0f, 0.0f};
    Vector expected = {1.0f, 0.0f, 0.0f};
    return AssertEq(v.Normalize(), expected);
  });

  framework->AddTest("Normalize vector 2", []() -> bool {
    Vector v = {1.0f, 2.0f, 3.0f};
    Vector expected = {1.0f / sqrt(14.0f), 2.0f / sqrt(14.0f),
                       3.0f / sqrt(14.0f)};
    return AssertEq(v.Normalize(), expected);
  });

  framework->AddTest("The magnitude of a normalized vector", []() -> bool {
    Vector v = {1.0f, 2.0f, 3.0f};

    Vector nv = v.Normalize();
    float mn = nv.Magnitude();

    float expected = 1.0f;

    return AssertFloatEq(mn, expected);
  });

  framework->AddTest("The dot product (self)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};
    float result = v1.DotProduct(v2);
    float expected = 20.0f;

    return AssertFloatEq(result, expected);
  });

  framework->AddTest("The dot product (separate)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};
    float result = DotProduct(v1, v2);
    float expected = 20.0f;

    return AssertFloatEq(result, expected);
  });

  framework->AddTest("The cross product (self)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = v1.CrossProduct(v2);
    Vector expected = {-1.0f, 2.0f, -1.0f};

    return AssertEq(result, expected);
  });

  framework->AddTest("The cross product (self, reversed)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = v2.CrossProduct(v1);
    Vector expected = {1.0f, -2.0f, 1.0f};

    return AssertEq(result, expected);
  });

  framework->AddTest("The cross product (separate)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = CrossProduct(v1, v2);
    Vector expected = {-1.0f, 2.0f, -1.0f};

    return AssertEq(result, expected);
  });

  framework->AddTest("The cross product (separate, reversed)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = CrossProduct(v2, v1);
    Vector expected = {1.0f, -2.0f, 1.0f};

    return AssertEq(result, expected);
  });
}
