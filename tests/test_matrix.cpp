#include <src/matrix.h>
#include <src/test_suite.h>
#include <tests/test_matrix.h>

void TestMatrix(TestFramework *framework) {
  framework->AddTest("Initialize matrix", []() -> bool {
    Matrix matrix = {4, 4};

    matrix.Populate(1.0f, 2.0f, 3.0f, 4.0f, 5.5f, 6.5f, 7.5f, 8.5f, 9.0f, 10.0f,
                    11.0f, 12.0f, 13.5f, 14.5f, 15.5f, 16.5f);

    bool res = AssertFloatEq(matrix.At(0, 0), 1.0f) &&
               AssertFloatEq(matrix.At(0, 3), 4.0f) &&
               AssertFloatEq(matrix.At(1, 0), 5.5f) &&
               AssertFloatEq(matrix.At(1, 2), 7.5f) &&
               AssertFloatEq(matrix.At(2, 2), 11.0f) &&
               AssertFloatEq(matrix.At(3, 0), 13.5f) &&
               AssertFloatEq(matrix.At(3, 2), 15.5f);

    return res;
  });
}
