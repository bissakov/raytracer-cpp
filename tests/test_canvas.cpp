#include <src/canvas.h>
#include <src/test_suite.h>
#include <tests/test_canvas.h>

void TestCanvas(TestFramework *framework) {
  framework->AddTest("Create canvas", []() -> bool {
    Canvas canvas = {10, 20};
    return AssertEq(canvas.width, 10) && AssertEq(canvas.height, 20);
  });

  framework->AddTest("Check all default canvas colors (black)", []() -> bool {
    Canvas canvas = {10, 20};
    Color black = {0, 0, 0};

    bool res = true;
    for (int i = 0; i < canvas.height; ++i) {
      for (int j = 0; j < canvas.width; ++j) {
        Pixel current_pixel = canvas.PixelAt(j, i);
        res = res && (current_pixel.color == black);
      }
    }

    return AssertEq(res, true);
  });

  framework->AddTest("Write color of the pixel", []() -> bool {
    Canvas canvas = {5, 10};
    Color red = {1, 0, 0};

    int x = 2;
    int y = 3;
    canvas.WritePixelColor(x, y, red);
    Pixel red_pixel = canvas.PixelAt(2, 3);

    return AssertEq(red_pixel.color, red) && AssertEq(red_pixel.x, x) &&
           AssertEq(red_pixel.y, y);
  });
}
