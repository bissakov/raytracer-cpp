#include <src/canvas.h>
#include <src/file_io.h>
#include <src/main.h>
#include <src/matrix.h>
#include <src/pixel.h>
#include <src/point_vector.h>
#include <src/test_suite.h>
#include <tests/tests.h>

#include <cmath>
#include <string>

void RunTests(const std::string root_folder_path) {
  TestFramework framework;
  framework.root_folder_path = root_folder_path;

  framework.AddTest("Adding point to vector", []() -> bool {
    Point left = {3.0f, -2.0f, 5.0f};
    Vector right = {-2.0f, 3.0f, 1.0f};
    Point expected = {1.0f, 1.0f, 6.0f};
    return AssertEq(left + right, expected);
  });

  framework.AddTest("Subtracting point from point", []() -> bool {
    Point left = {3.0f, 2.0f, 1.0f};
    Point right = {-2.0f, 3.0f, 1.0f};
    Vector expected = {5.0f, -1.0f, 0.0f};
    return AssertEq(left - right, expected);
  });

  framework.AddTest("Subtracting vector from point", []() -> bool {
    Point left = {3.0f, 2.0f, 1.0f};
    Vector right = {5.0f, 6.0f, 7.0f};
    Point expected = {-2.0f, -4.0f, -6.0f};
    return AssertEq(left - right, expected);
  });

  framework.AddTest("Subtracting vector from vector", []() -> bool {
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

  framework.AddTest("Multiply vector by scalar", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {3.5f, -7.0f, 10.5f};
    return AssertEq(v * 3.5f, expected);
  });

  framework.AddTest("Divide vector by multiplying by scalar", []() -> bool {
    Vector v = {1.0f, -2.0f, 3.0f};
    Vector expected = {0.5f, -1.0f, 1.5f};
    return AssertEq(v * 0.5f, expected);
  });

  framework.AddTest("Divide vector by scalar", []() -> bool {
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

  framework.AddTest("The dot product (self)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};
    float result = v1.DotProduct(v2);
    float expected = 20.0f;

    return AssertFloatEq(result, expected);
  });

  framework.AddTest("The dot product (separate)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};
    float result = DotProduct(v1, v2);
    float expected = 20.0f;

    return AssertFloatEq(result, expected);
  });

  framework.AddTest("The cross product (self)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = v1.CrossProduct(v2);
    Vector expected = {-1.0f, 2.0f, -1.0f};

    return AssertEq(result, expected);
  });

  framework.AddTest("The cross product (self, reversed)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = v2.CrossProduct(v1);
    Vector expected = {1.0f, -2.0f, 1.0f};

    return AssertEq(result, expected);
  });

  framework.AddTest("The cross product (separate)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = CrossProduct(v1, v2);
    Vector expected = {-1.0f, 2.0f, -1.0f};

    return AssertEq(result, expected);
  });

  framework.AddTest("The cross product (separate, reversed)", []() -> bool {
    Vector v1 = {1.0f, 2.0f, 3.0f};
    Vector v2 = {2.0f, 3.0f, 4.0f};

    Vector result = CrossProduct(v2, v1);
    Vector expected = {1.0f, -2.0f, 1.0f};

    return AssertEq(result, expected);
  });

  framework.AddTest("Adding color to color", []() -> bool {
    Color left = {0.9f, 0.6f, 0.75f};
    Color right = {0.7f, 0.1f, 0.25f};
    Color expected = {1.6f, 0.7f, 1.0f};
    return AssertEq(left + right, expected);
  });

  framework.AddTest("Subtracting color from color", []() -> bool {
    Color left = {0.9f, 0.6f, 0.75f};
    Color right = {0.7f, 0.1f, 0.25f};
    Color expected = {0.2f, 0.5f, 0.5f};
    return AssertEq(left - right, expected);
  });

  framework.AddTest("Multiply color by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color expected = {0.4f, 0.6f, 0.8f};
    return AssertEq(c * 2.0f, expected);
  });

  framework.AddTest("Divide color by multiplying by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color expected = {0.1f, 0.15f, 0.2f};
    return AssertEq(c * 0.5f, expected);
  });

  framework.AddTest("Divide color by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color expected = {0.1f, 0.15f, 0.2f};
    return AssertEq(c / 2.0f, expected);
  });

  framework.AddTest("Multiply colors", []() -> bool {
    Color left = {1.0f, 0.2f, 0.4f};
    Color right = {0.9f, 1.0f, 0.1f};
    Color expected = {0.9f, 0.2f, 0.04f};
    return AssertEq(left * right, expected);
  });

  framework.AddTest("Create canvas", []() -> bool {
    Canvas canvas = {10, 20};
    return AssertEq(canvas.width, 10) && AssertEq(canvas.height, 20);
  });

  framework.AddTest("Check all default canvas colors (black)", []() -> bool {
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

  framework.AddTest("Write color of the pixel", []() -> bool {
    Canvas canvas = {5, 10};
    Color red = {1, 0, 0};

    int x = 2;
    int y = 3;
    canvas.WritePixelColor(x, y, red);
    Pixel red_pixel = canvas.PixelAt(2, 3);

    return AssertEq(red_pixel.color, red) && AssertEq(red_pixel.x, x) &&
           AssertEq(red_pixel.y, y);
  });

  framework.AddTest("Save canvas to PPM", [framework]() -> bool {
    Canvas canvas = {500, 300};

    Color blue = {0, 0.34f, 0.72f};
    Color yellow = {1, 0.85f, 0};

    int stripe_thickness = 20;

    for (int j = 0; j < canvas.height; ++j) {
      for (int i = 0; i < canvas.width; ++i) {
        if ((i / stripe_thickness + j / stripe_thickness) % 2 == 0) {
          canvas.WritePixelColor(i, j, blue);
        } else {
          canvas.WritePixelColor(i, j, yellow);
        }
      }
    }

    std::string file_path = framework.root_folder_path + "\\data\\canvas.ppm";
    bool res = canvas.SaveToPPM(file_path);

    return AssertEq(res, true);
  });

  framework.AddTest("Load canvas from PPM", [framework]() -> bool {
    Canvas canvas = {0, 0};

    const std::string input_file_path =
        framework.root_folder_path + "\\data\\canvas.ppm";
    bool res1 = canvas.LoadFromPPM(input_file_path);

    const std::string output_file_path =
        framework.root_folder_path + "\\data\\canvas_output.ppm";
    bool res2 = canvas.SaveToPPM(output_file_path);

    bool are_files_same = CompareFiles(input_file_path, output_file_path);

    return AssertEq(are_files_same, res1 == res2);
  });

  framework.AddTest("Map the trajectory of projectile", [framework]() -> bool {
    Canvas canvas = {900, 550};

    Projectile proj;
    proj.position = {0.0f, 1.0f, 0.0f};
    proj.velocity = {1.0f, 1.8f, 0.0f};
    proj.velocity = proj.velocity.Normalize() * 11.25f;

    Environment env;
    env.gravity = {0.0f, -0.1f, 0.0f};
    env.wind = {-0.01f, 0.0f, 0.0f};

    Color red = {1.0f, 0.0f, 0.0f};

    while (proj.position.y > 0.0f) {
      int pos_x = static_cast<int>(floor(proj.position.x));
      int pos_y = static_cast<int>(floor(proj.position.y));
      pos_y = static_cast<int>(abs(canvas.height - floor(proj.position.y)));

      if (canvas.IsPixelInRange(pos_x, pos_y)) {
        canvas.WritePixelColor(pos_x, pos_y, red);
      }

      proj.position = proj.position + proj.velocity;
      proj.velocity = proj.velocity + env.gravity + env.wind;
    }

    std::string output_file_path =
        framework.root_folder_path + "\\data\\projectile.ppm";
    bool res = canvas.SaveToPPM(output_file_path);

    return AssertEq(res, true);
  });

  framework.AddTest("Initialize 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    return AssertEq(matrix.rows, 4) && AssertEq(matrix.cols, 4);
  });

  framework.AddTest("Initialize 3x3 matrix", []() -> bool {
    Matrix matrix = {3, 3};
    return AssertEq(matrix.rows, 3) && AssertEq(matrix.cols, 3);
  });

  framework.AddTest("Initialize 2x2 matrix", []() -> bool {
    Matrix matrix = {2, 2};
    return AssertEq(matrix.rows, 2) && AssertEq(matrix.cols, 2);
  });

  framework.AddTest("Check 4x4 matrix values", []() -> bool {
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

  framework.AddTest("Check 3x3 matrix values", []() -> bool {
    Matrix matrix = {3, 3};

    matrix.Populate(-3.0f, 5.0f, 0.0f, 1.0f, -2.0f, -7.0f, 0.0f, 1.0f, 1.0f);

    bool res = AssertFloatEq(matrix.At(0, 0), -3.0f) &&
               AssertFloatEq(matrix.At(1, 1), -2.0f) &&
               AssertFloatEq(matrix.At(2, 2), 1.0f);

    return res;
  });

  framework.AddTest("Check 2x2 matrix values", []() -> bool {
    Matrix matrix = {2, 2};

    matrix.Populate(-3.0f, 5.0f, 1.0f, -2.0f);

    bool res = AssertFloatEq(matrix.At(0, 0), -3.0f) &&
               AssertFloatEq(matrix.At(0, 1), 5.0f) &&
               AssertFloatEq(matrix.At(1, 0), 1.0f) &&
               AssertFloatEq(matrix.At(1, 1), -2.0f);

    return res;
  });

  framework.AddTest("Compare two equal 4x4 matrices", []() -> bool {
    Matrix matrix1 = {4, 4};
    matrix1.Populate(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 8.0f,
                     7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f);
    Matrix matrix2 = {4, 4};
    matrix2.Populate(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 8.0f,
                     7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f);

    bool res = AssertEq(matrix1, matrix2);
    return res;
  });

  framework.RunTest();
}
