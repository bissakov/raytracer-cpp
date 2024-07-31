#include <src/canvas.h>
#include <src/file_io.h>
#include <src/main.h>
#include <src/matrix.h>
#include <src/pixel.h>
#include <src/point_vector.h>
#include <src/test_suite.h>
#include <tests/tests.h>

#include <cmath>
#include <functional>
#include <string>

void RunTests(const std::string root_folder_path) {
  TestFramework framework;
  framework.root_folder_path = root_folder_path;

  framework.AddTest("Adding point to vector", []() -> bool {
    Point left = {3, -2, 5};
    Vector right = {-2, 3, 1};
    Point actual = left + right;
    Point expected = {1, 1, 6};
    return ASSERT_EQUAL_POINTS(actual, expected);
  });

  framework.AddTest("Subtracting point from point", []() -> bool {
    Point left = {3, 2, 1};
    Point right = {-2, 3, 1};
    Vector actual = left - right;
    Vector expected = {5, -1, 0};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Subtracting vector from point", []() -> bool {
    Point left = {3, 2, 1};
    Vector right = {5, 6, 7};
    Point actual = left - right;
    Point expected = {-2, -4, -6};
    return ASSERT_EQUAL_POINTS(actual, expected);
  });

  framework.AddTest("Subtracting vector from vector", []() -> bool {
    Vector left = {3, 2, 1};
    Vector right = {5, 6, 7};
    Vector actual = left - right;
    Vector expected = {-2, -4, -6};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Negate vector", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = -v;
    Vector expected = {-1, 2, -3};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Multiply vector by scalar", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v * 3.5f;
    Vector expected = {3.5f, -7, 10.5f};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Divide vector by multiplying by scalar", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v * 0.5f;
    Vector expected = {0.5f, -1, 1.5f};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Divide vector by scalar", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v / 2;
    Vector expected = {0.5f, -1, 1.5f};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("The magnitude of a vector 1", []() -> bool {
    Vector v = {1, 0, 0};
    float actual = v.Magnitude();
    float expected = 1;
    return ASSERT_EQUAL_FLOATS(actual, expected);
  });

  framework.AddTest("The magnitude of a vector 2", []() -> bool {
    Vector v = {0, 1, 0};
    float actual = v.Magnitude();
    float expected = 1;
    return ASSERT_EQUAL_FLOATS(actual, expected);
  });

  framework.AddTest("The magnitude of a vector 3", []() -> bool {
    Vector v = {0, 0, 1};
    float actual = v.Magnitude();
    float expected = 1;
    return ASSERT_EQUAL_FLOATS(actual, expected);
  });

  framework.AddTest("The magnitude of a vector 4", []() -> bool {
    Vector v = {1, 2, 3};
    float actual = v.Magnitude();
    float expected = sqrt(14.0f);
    return ASSERT_EQUAL_FLOATS(actual, expected);
  });

  framework.AddTest("The magnitude of a vector 5", []() -> bool {
    Vector v = {-1, -2, -3};
    float actual = v.Magnitude();
    float expected = sqrt(14.0f);
    return ASSERT_EQUAL_FLOATS(actual, expected);
  });

  framework.AddTest("Normalize vector 1", []() -> bool {
    Vector v = {4, 0, 0};
    Vector actual = v.Normalize();
    Vector expected = {1, 0, 0};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Normalize vector 2", []() -> bool {
    Vector v = {1, 2, 3};
    Vector actual = v.Normalize();
    Vector expected = {1 / sqrt(14.0f), 2 / sqrt(14.0f), 3 / sqrt(14.0f)};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("The magnitude of a normalized vector", []() -> bool {
    Vector v = {1, 2, 3};
    Vector nv = v.Normalize();
    float actual = nv.Magnitude();
    float expected = 1;
    return ASSERT_EQUAL_FLOATS(actual, expected);
  });

  framework.AddTest("The dot product (self)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    float result = v1.DotProduct(v2);
    float expected = 20;

    return ASSERT_EQUAL_FLOATS(result, expected);
  });

  framework.AddTest("The dot product (separate)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    float result = DotProduct(v1, v2);
    float expected = 20;

    return ASSERT_EQUAL_FLOATS(result, expected);
  });

  framework.AddTest("The cross product (self)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v1.CrossProduct(v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("The cross product (self, reversed)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v2.CrossProduct(v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("The cross product (separate)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v1, v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("The cross product (separate, reversed)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v2, v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Adding color to color", []() -> bool {
    Color left = {0.9f, 0.6f, 0.75f};
    Color right = {0.7f, 0.1f, 0.25f};
    Color actual = left + right;
    Color expected = {1.6f, 0.7f, 1};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  framework.AddTest("Subtracting color from color", []() -> bool {
    Color left = {0.9f, 0.6f, 0.75f};
    Color right = {0.7f, 0.1f, 0.25f};
    Color actual = left - right;
    Color expected = {0.2f, 0.5f, 0.5f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  framework.AddTest("Multiply color by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color actual = c * 2;
    Color expected = {0.4f, 0.6f, 0.8f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  framework.AddTest("Divide color by multiplying by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color actual = c * 0.5f;
    Color expected = {0.1f, 0.15f, 0.2f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  framework.AddTest("Divide color by scalar", []() -> bool {
    Color c = {0.2f, 0.3f, 0.4f};
    Color actual = c / 2;
    Color expected = {0.1f, 0.15f, 0.2f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  framework.AddTest("Multiply colors", []() -> bool {
    Color left = {1, 0.2f, 0.4f};
    Color right = {0.9f, 1, 0.1f};
    Color actual = left * right;
    Color expected = {0.9f, 0.2f, 0.04f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  framework.AddTest("Create canvas", []() -> bool {
    Canvas canvas = {10, 20};
    int actual_width = canvas.width;
    int actual_height = canvas.height;
    int expected_width = 10;
    int expected_height = 20;
    return ASSERT_EQUAL_INTS(actual_width, expected_width) &&
           ASSERT_EQUAL_INTS(actual_height, expected_height);
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

    return ASSERT_EQUAL_BOOLS(res, true);
  });

  framework.AddTest("Write color of the pixel", []() -> bool {
    Canvas canvas = {5, 10};
    Color red = {1, 0, 0};

    int x = 2;
    int y = 3;
    canvas.WritePixelColor(x, y, red);
    Pixel pixel = canvas.PixelAt(x, y);
    Color actual_color = pixel.color;

    return ASSERT_EQUAL_COLORS(actual_color, red) &&
           ASSERT_EQUAL_INTS(pixel.x, x) && ASSERT_EQUAL_INTS(pixel.y, y);
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

    return ASSERT_EQUAL_BOOLS(res, true);
  });

  framework.AddTest("Load canvas from PPM", [framework]() -> bool {
    Canvas canvas = {0, 0};

    const std::string input_path =
        framework.root_folder_path + "\\data\\canvas.ppm";
    bool res1 = canvas.LoadFromPPM(input_path);

    const std::string output_path =
        framework.root_folder_path + "\\data\\canvas_output.ppm";
    bool res2 = canvas.SaveToPPM(output_path);

    bool actual = CompareFiles(input_path, output_path) && res1 && res2;
    bool expected = true;
    return ASSERT_EQUAL_BOOLS(actual, expected);
  });

  framework.AddTest("Map the trajectory of projectile", [framework]() -> bool {
    Canvas canvas = {900, 550};

    Projectile proj;
    proj.position = {0, 1, 0};
    proj.velocity = {1, 1.8f, 0};
    proj.velocity = proj.velocity.Normalize() * 11.25f;

    Environment env;
    env.gravity = {0, -0.1f, 0};
    env.wind = {-0.01f, 0, 0};

    Color red = {1, 0, 0};

    while (proj.position.y > 0) {
      int pos_x = static_cast<int>(floor(proj.position.x));
      int pos_y = static_cast<int>(floor(proj.position.y));
      pos_y = static_cast<int>(abs(canvas.height - floor(proj.position.y)));

      if (canvas.IsPixelInRange(pos_x, pos_y)) {
        canvas.WritePixelColor(pos_x, pos_y, red);
      }

      proj.position = proj.position + proj.velocity;
      proj.velocity = proj.velocity + env.gravity + env.wind;
    }

    std::string output_path =
        framework.root_folder_path + "\\data\\projectile.ppm";
    bool res = canvas.SaveToPPM(output_path);

    return ASSERT_EQUAL_BOOLS(res, true);
  });

  framework.AddTest("Initialize 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    return ASSERT_EQUAL_INTS(matrix.rows, 4) &&
           ASSERT_EQUAL_INTS(matrix.cols, 4);
  });

  framework.AddTest("Initialize 3x3 matrix", []() -> bool {
    Matrix matrix = {3, 3};
    return ASSERT_EQUAL_INTS(matrix.rows, 3) &&
           ASSERT_EQUAL_INTS(matrix.cols, 3);
  });

  framework.AddTest("Initialize 2x2 matrix", []() -> bool {
    Matrix matrix = {2, 2};
    return ASSERT_EQUAL_INTS(matrix.rows, 2) &&
           ASSERT_EQUAL_INTS(matrix.cols, 2);
  });

  framework.AddTest("Check 4x4 matrix values", []() -> bool {
    Matrix matrix = {4, 4};
    int element_count = matrix.rows * matrix.cols;
    float elements[] = {1, 2,  3,  4,  5.5f,  6.5f,  7.5f,  8.5f,
                        9, 10, 11, 12, 13.5f, 14.5f, 15.5f, 16.5f};
    matrix.Populate(elements, element_count);

    bool res = ASSERT_EQUAL_FLOATS(matrix.At(0, 0), 1) &&
               ASSERT_EQUAL_FLOATS(matrix.At(0, 3), 4) &&
               ASSERT_EQUAL_FLOATS(matrix.At(1, 0), 5.5f) &&
               ASSERT_EQUAL_FLOATS(matrix.At(1, 2), 7.5f) &&
               ASSERT_EQUAL_FLOATS(matrix.At(2, 2), 11) &&
               ASSERT_EQUAL_FLOATS(matrix.At(3, 0), 13.5f) &&
               ASSERT_EQUAL_FLOATS(matrix.At(3, 2), 15.5f);

    return res;
  });

  framework.AddTest("Check 3x3 matrix values", []() -> bool {
    Matrix matrix = {3, 3};
    int element_count = matrix.rows * matrix.cols;
    float elements[] = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    matrix.Populate(elements, element_count);

    bool res = ASSERT_EQUAL_FLOATS(matrix.At(0, 0), -3) &&
               ASSERT_EQUAL_FLOATS(matrix.At(1, 1), -2) &&
               ASSERT_EQUAL_FLOATS(matrix.At(2, 2), 1);

    return res;
  });

  framework.AddTest("Check 2x2 matrix values", []() -> bool {
    Matrix matrix = {2, 2};
    int element_count = matrix.rows * matrix.cols;
    float elements[] = {-3, 5, 1, -2};
    matrix.Populate(elements, element_count);

    bool res = ASSERT_EQUAL_FLOATS(matrix.At(0, 0), -3) &&
               ASSERT_EQUAL_FLOATS(matrix.At(0, 1), 5) &&
               ASSERT_EQUAL_FLOATS(matrix.At(1, 0), 1) &&
               ASSERT_EQUAL_FLOATS(matrix.At(1, 1), -2);

    return res;
  });

  framework.AddTest("Compare two equal 4x4 matrices", []() -> bool {
    Matrix matrix1 = {4, 4};
    int element_count1 = matrix1.rows * matrix1.cols;
    float elements1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, element_count1);

    Matrix matrix2 = {4, 4};
    int element_count2 = matrix2.rows * matrix2.cols;
    float elements2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, element_count2);

    bool res = matrix1 == matrix2;
    return ASSERT_EQUAL_BOOLS(res, true);
  });

  framework.AddTest("Compare two different 4x4 matrices", []() -> bool {
    Matrix matrix1 = {4, 4};
    int element_count1 = matrix1.rows * matrix1.cols;
    float elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, element_count1);

    Matrix matrix2 = {4, 4};
    int element_count2 = matrix2.rows * matrix2.cols;
    float elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, element_count2);

    bool res = matrix1 != matrix2;
    return ASSERT_EQUAL_BOOLS(res, true);
  });

  framework.AddTest("Compare two differently sized matrices", []() -> bool {
    Matrix matrix1 = {3, 3};
    int element_count1 = matrix1.rows * matrix1.cols;
    float elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9};
    matrix1.Populate(elements1, element_count1);

    Matrix matrix2 = {4, 4};
    int element_count2 = matrix2.rows * matrix2.cols;
    float elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, element_count2);

    bool res = matrix1 != matrix2;
    return ASSERT_EQUAL_BOOLS(res, true);
  });

  framework.AddTest("Multiply two 4x4 matrices", []() -> bool {
    Matrix matrix1 = {4, 4};
    int element_count1 = matrix1.rows * matrix1.cols;
    float elements1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, element_count1);

    Matrix matrix2 = {4, 4};
    int element_count2 = matrix2.rows * matrix2.cols;
    float elements2[] = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
    matrix2.Populate(elements2, element_count2);

    Matrix actual = matrix1 * matrix2;

    Matrix expected = {4, 4};
    int expected_elements_count = expected.rows * expected.cols;
    float expected_elements[] = {20, 22, 50,  48,  44, 54, 114, 108,
                                 40, 58, 110, 102, 16, 26, 46,  42};
    expected.Populate(expected_elements, expected_elements_count);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  framework.AddTest("Multiply a 4x4 matrix by a vector", []() -> bool {
    Matrix matrix = {4, 4};
    int element_count1 = matrix.rows * matrix.cols;
    float elements1[] = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
    matrix.Populate(elements1, element_count1);

    Vector vector = {1, 2, 3, 1};

    Vector actual = matrix * vector;

    Vector expected = {18, 24, 33, 1};

    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  framework.AddTest("Multiply a matrix by an identity matrix", []() -> bool {
    Matrix matrix = {4, 4};
    int element_count1 = matrix.rows * matrix.cols;
    float elements1[] = {0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
    matrix.Populate(elements1, element_count1);

    Matrix identity_matrix = IdentityMatrix();
    Matrix actual = matrix * identity_matrix;

    return ASSERT_EQUAL_MATRICES(actual, matrix);
  });

  framework.AddTest("Transpose a 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    int element_count1 = matrix.rows * matrix.cols;
    float elements1[] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
    matrix.Populate(elements1, element_count1);

    Matrix transposed_matrix = matrix.Transpose();

    Matrix expected = {4, 4};
    int element_count2 = matrix.rows * matrix.cols;
    float elements2[] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
    matrix.Populate(elements2, element_count2);

    return ASSERT_EQUAL_MATRICES(transposed_matrix, matrix);
  });

  framework.AddTest("Transpose an identity matrix", []() -> bool {
    Matrix identity_matrix = IdentityMatrix();
    Matrix actual = identity_matrix.Transpose();

    Matrix expected = {4, 4};
    float expected_elements[] = {1, 0, 0, 0, 0, 1, 0, 0,
                                 0, 0, 1, 0, 0, 0, 0, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  framework.AddTest("Determinant of a 2x2 matrix", []() -> bool {
    Matrix matrix = {2, 2};
    float elements[] = {1, 5, -3, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Determinant();
    float expected = 17.0f;

    return ASSERT_EQUAL_FLOATS(actual, expected);
  });

  framework.AddTest("Submatrix of a 3x3 matrix", []() -> bool {
    Matrix matrix = {3, 3};
    float elements[] = {1, 5, 0, -3, 2, 7, 0, 6, -3};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(0, 2);

    Matrix expected = {2, 2};
    float expected_elements[] = {-3, 2, 0, 6};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  framework.AddTest("Submatrix of a 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    float elements[] = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(2, 1);

    Matrix expected = {3, 3};
    float expected_elements[] = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  framework.RunTest();
}
