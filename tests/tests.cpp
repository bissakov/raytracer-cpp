#include <src/canvas.h>
#include <src/main.h>
#include <src/pixel.h>
#include <src/point_vector.h>
#include <src/test_suite.h>
#include <tests/test_canvas.h>
#include <tests/test_color.h>
#include <tests/test_point_vector.h>
#include <tests/tests.h>

int RunTests() {
  TestFramework framework;

  TestPointVector(&framework);
  TestColor(&framework);
  TestCanvas(&framework);

  framework.RunTest();

  return 0;
}
