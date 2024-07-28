#include <src/canvas.h>
#include <src/main.h>
#include <src/pixel.h>
#include <src/point_vector.h>
#include <src/test_suite.h>
#include <tests/test_canvas.h>
#include <tests/test_color.h>
#include <tests/test_matrix.h>
#include <tests/test_point_vector.h>
#include <tests/tests.h>

#include <string>

void RunTests(std::string root_folder_path) {
  TestFramework framework;
  framework.root_folder_path = root_folder_path;

  TestPointVector(&framework);
  TestColor(&framework);
  TestCanvas(&framework);
  TestMatrix(&framework);

  framework.RunTest();
}
