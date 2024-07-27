#include <src/pixel.h>
#include <src/test_suite.h>
#include <tests/test_color.h>

void TestColor(TestFramework *framework) {
  framework->AddTest("Adding color to color", []() -> bool {
    Color left = {0.9f, 0.6f, 0.75f};
    Color right = {0.7f, 0.1f, 0.25f};
    Color expected = {1.6f, 0.7f, 1.0f};
    return AssertEq(left + right, expected);
  });

  framework->AddTest("Subtracting color from color", []() -> bool {
    Color left = {0.9f, 0.6f, 0.75f};
    Color right = {0.7f, 0.1f, 0.25f};
    Color expected = {0.2f, 0.5f, 0.5f};
    return AssertEq(left - right, expected);
  });

  framework->AddTest("Multiply color by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color expected = {0.4f, 0.6f, 0.8f};
    return AssertEq(c * 2.0f, expected);
  });

  framework->AddTest("Divide color by multiplying by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color expected = {0.1f, 0.15f, 0.2f};
    return AssertEq(c * 0.5f, expected);
  });

  framework->AddTest("Divide color by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color expected = {0.1f, 0.15f, 0.2f};
    return AssertEq(c / 2.0f, expected);
  });

  framework->AddTest("Multiply colors", []() -> bool {
    Color left = {1.0f, 0.2f, 0.4f};
    Color right = {0.9f, 1.0f, 0.1f};
    Color expected = {0.9f, 0.2f, 0.04f};
    return AssertEq(left * right, expected);
  });
}
