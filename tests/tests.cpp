#include <src/canvas.h>
#include <src/file_io.h>
#include <src/main.h>
#include <src/matrix.h>
#include <src/pixel.h>
#include <src/point_vector.h>
#include <src/test_suite.h>
#include <tests/tests.h>

#include <string>

void RunTests(const std::string root_folder_path) {
  TestFramework fw;
  fw.root_folder_path = root_folder_path;

  fw.AddTest("Adding point to vector", []() -> bool {
    Point left = {3, -2, 5};
    Vector right = {-2, 3, 1};
    Point actual = left + right;
    Point expected = {1, 1, 6};
    return ASSERT_EQUAL_POINTS(actual, expected);
  });

  fw.AddTest("Subtracting point from point", []() -> bool {
    Point left = {3, 2, 1};
    Point right = {-2, 3, 1};
    Vector actual = left - right;
    Vector expected = {5, -1, 0};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Subtracting vector from point", []() -> bool {
    Point left = {3, 2, 1};
    Vector right = {5, 6, 7};
    Point actual = left - right;
    Point expected = {-2, -4, -6};
    return ASSERT_EQUAL_POINTS(actual, expected);
  });

  fw.AddTest("Subtracting vector from vector", []() -> bool {
    Vector left = {3, 2, 1};
    Vector right = {5, 6, 7};
    Vector actual = left - right;
    Vector expected = {-2, -4, -6};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Negate vector", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = -v;
    Vector expected = {-1, 2, -3};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Multiply vector by scalar", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v * 3.5;
    Vector expected = {3.5, -7, 10.5};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Divide vector by multiplying by scalar", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v * 0.5;
    Vector expected = {0.5, -1, 1.5};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Divide vector by scalar", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v / 2;
    Vector expected = {0.5, -1, 1.5};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("The magnitude of a vector 1", []() -> bool {
    Vector v = {1, 0, 0};
    double actual = v.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("The magnitude of a vector 2", []() -> bool {
    Vector v = {0, 1, 0};
    double actual = v.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("The magnitude of a vector 3", []() -> bool {
    Vector v = {0, 0, 1};
    double actual = v.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("The magnitude of a vector 4", []() -> bool {
    Vector v = {1, 2, 3};
    double actual = v.Magnitude();
    double expected = sqrt(14.0);
    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("The magnitude of a vector 5", []() -> bool {
    Vector v = {-1, -2, -3};
    double actual = v.Magnitude();
    double expected = sqrt(14.0);
    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("Normalize vector 1", []() -> bool {
    Vector v = {4, 0, 0};
    Vector actual = v.Normalize();
    Vector expected = {1, 0, 0};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Normalize vector 2", []() -> bool {
    Vector v = {1, 2, 3};
    Vector actual = v.Normalize();
    Vector expected = {1 / sqrt(14.0), 2 / sqrt(14.0), 3 / sqrt(14.0)};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("The magnitude of a normalized vector", []() -> bool {
    Vector v = {1, 2, 3};
    Vector nv = v.Normalize();
    double actual = nv.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("The dot product (self)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    double result = v1.DotProduct(v2);
    double expected = 20;

    return ASSERT_EQUAL_DOUBLES(result, expected);
  });

  fw.AddTest("The dot product (separate)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    double result = DotProduct(v1, v2);
    double expected = 20;

    return ASSERT_EQUAL_DOUBLES(result, expected);
  });

  fw.AddTest("The cross product (self)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v1.CrossProduct(v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("The cross product (self, reversed)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v2.CrossProduct(v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("The cross product (separate)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v1, v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("The cross product (separate, reversed)", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v2, v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Adding color to color", []() -> bool {
    Color left = {0.9, 0.6, 0.75f};
    Color right = {0.7, 0.1, 0.25f};
    Color actual = left + right;
    Color expected = {1.6, 0.7, 1};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  fw.AddTest("Subtracting color from color", []() -> bool {
    Color left = {0.9, 0.6, 0.75f};
    Color right = {0.7, 0.1, 0.25f};
    Color actual = left - right;
    Color expected = {0.2, 0.5, 0.5f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  fw.AddTest("Multiply color by scalar", []() -> bool {
    Color c = {0.2, 0.3, 0.4f};
    Color actual = c * 2;
    Color expected = {0.4, 0.6, 0.8f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  fw.AddTest("Divide color by multiplying by scalar", []() -> bool {
    Color c = {0.2, 0.3, 0.4f};
    Color actual = c * 0.5;
    Color expected = {0.1, 0.15, 0.2f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  fw.AddTest("Divide color by scalar", []() -> bool {
    Color c = {0.2, 0.3, 0.4f};
    Color actual = c / 2;
    Color expected = {0.1, 0.15, 0.2f};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  fw.AddTest("Multiply colors", []() -> bool {
    Color left = {1, 0.2, 0.4};
    Color right = {0.9, 1, 0.1};
    Color actual = left * right;
    Color expected = {0.9, 0.2, 0.04};
    return ASSERT_EQUAL_COLORS(actual, expected);
  });

  fw.AddTest("Create canvas", []() -> bool {
    Canvas canvas = {10, 20};
    size_t actual_width = canvas.width;
    size_t actual_height = canvas.height;
    size_t expected_width = 10;
    size_t expected_height = 20;
    return ASSERT_EQUAL_SIZE_T(actual_width, expected_width) &&
           ASSERT_EQUAL_SIZE_T(actual_height, expected_height);
  });

  fw.AddTest("Check all default canvas colors (black)", []() -> bool {
    Canvas canvas = {10, 20};
    Color black = {0, 0, 0};

    bool res = true;
    for (size_t i = 0; i < canvas.height; ++i) {
      for (size_t j = 0; j < canvas.width; ++j) {
        Pixel current_pixel = canvas.PixelAt(j, i);
        res = res && (current_pixel.color == black);
      }
    }

    return ASSERT_EQUAL_BOOLS(res, true);
  });

  fw.AddTest("Write color of the pixel", []() -> bool {
    Canvas canvas = {5, 10};
    Color red = {1, 0, 0};

    size_t x = 2;
    size_t y = 3;
    canvas.WritePixelColor(x, y, red);
    Pixel pixel = canvas.PixelAt(x, y);
    Color actual_color = pixel.color;

    return ASSERT_EQUAL_COLORS(actual_color, red) &&
           ASSERT_EQUAL_SIZE_T(pixel.x, x) && ASSERT_EQUAL_SIZE_T(pixel.y, y);
  });

  fw.AddTest("Save canvas to PPM", [fw]() -> bool {
    Canvas canvas = {500, 300};

    Color blue = {0, 0.34, 0.72f};
    Color yellow = {1, 0.85, 0};

    size_t stripe_thickness = 20;

    for (size_t j = 0; j < canvas.height; ++j) {
      for (size_t i = 0; i < canvas.width; ++i) {
        if ((i / stripe_thickness + j / stripe_thickness) % 2 == 0) {
          canvas.WritePixelColor(i, j, blue);
        } else {
          canvas.WritePixelColor(i, j, yellow);
        }
      }
    }

    std::string file_path = fw.root_folder_path + "\\data\\canvas.ppm";
    bool res = canvas.SaveToPPM(file_path);

    return ASSERT_EQUAL_BOOLS(res, true);
  });

  fw.AddTest("Load canvas from PPM", [fw]() -> bool {
    Canvas canvas = {0, 0};

    const std::string input_path = fw.root_folder_path + "\\data\\canvas.ppm";
    bool res1 = canvas.LoadFromPPM(input_path);

    const std::string output_path =
        fw.root_folder_path + "\\data\\canvas_output.ppm";
    bool res2 = canvas.SaveToPPM(output_path);

    bool actual = CompareFiles(input_path, output_path) && res1 && res2;
    bool expected = true;
    return ASSERT_EQUAL_BOOLS(actual, expected);
  });

  fw.AddTest("Map the trajectory of projectile", [fw]() -> bool {
    Canvas canvas = {900, 550};

    Projectile proj;
    proj.position = {0, 1, 0};
    proj.velocity = {1, 1.8, 0};
    proj.velocity = proj.velocity.Normalize() * 11.25;

    Environment env;
    env.gravity = {0, -0.1, 0};
    env.wind = {-0.01, 0, 0};

    Color red = {1, 0, 0};

    while (proj.position.y > 0) {
      size_t pos_x = static_cast<size_t>(floor(proj.position.x));
      size_t pos_y = static_cast<size_t>(floor(proj.position.y));
      pos_y = static_cast<size_t>(
          abs(static_cast<double>(canvas.height) - floor(proj.position.y)));

      if (canvas.IsPixelInRange(pos_x, pos_y)) {
        canvas.WritePixelColor(pos_x, pos_y, red);
      }

      proj.position = proj.position + proj.velocity;
      proj.velocity = proj.velocity + env.gravity + env.wind;
    }

    std::string output_path = fw.root_folder_path + "\\data\\projectile.ppm";
    bool res = canvas.SaveToPPM(output_path);

    return ASSERT_EQUAL_BOOLS(res, true);
  });

  fw.AddTest("Initialize 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    return ASSERT_EQUAL_SIZE_T(matrix.rows, 4) &&
           ASSERT_EQUAL_SIZE_T(matrix.cols, 4);
  });

  fw.AddTest("Initialize 3x3 matrix", []() -> bool {
    Matrix matrix = {3, 3};
    return ASSERT_EQUAL_SIZE_T(matrix.rows, 3) &&
           ASSERT_EQUAL_SIZE_T(matrix.cols, 3);
  });

  fw.AddTest("Initialize 2x2 matrix", []() -> bool {
    Matrix matrix = {2, 2};
    return ASSERT_EQUAL_SIZE_T(matrix.rows, 2) &&
           ASSERT_EQUAL_SIZE_T(matrix.cols, 2);
  });

  fw.AddTest("Check 4x4 matrix values", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {1, 2,  3,  4,  5.5,  6.5f,  7.5f,  8.5f,
                         9, 10, 11, 12, 13.5, 14.5f, 15.5f, 16.5f};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL_DOUBLES(matrix.At(0, 0), 1) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(0, 3), 4) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(1, 0), 5.5) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(1, 2), 7.5) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(2, 2), 11) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(3, 0), 13.5) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(3, 2), 15.5);

    return res;
  });

  fw.AddTest("Check 3x3 matrix values", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL_DOUBLES(matrix.At(0, 0), -3) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(1, 1), -2) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(2, 2), 1);

    return res;
  });

  fw.AddTest("Check 2x2 matrix values", []() -> bool {
    Matrix matrix = {2, 2};
    double elements[] = {-3, 5, 1, -2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL_DOUBLES(matrix.At(0, 0), -3) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(0, 1), 5) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(1, 0), 1) &&
               ASSERT_EQUAL_DOUBLES(matrix.At(1, 1), -2);

    return res;
  });

  fw.AddTest("Compare two equal 4x4 matrices", []() -> bool {
    Matrix matrix1 = {4, 4};
    double elements1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    bool res = matrix1 == matrix2;
    return ASSERT_EQUAL_BOOLS(res, true);
  });

  fw.AddTest("Compare two different 4x4 matrices", []() -> bool {
    Matrix matrix1 = {4, 4};
    double elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    bool res = matrix1 != matrix2;
    return ASSERT_EQUAL_BOOLS(res, true);
  });

  fw.AddTest("Compare two differently sized matrices", []() -> bool {
    Matrix matrix1 = {3, 3};
    double elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    bool res = matrix1 != matrix2;
    return ASSERT_EQUAL_BOOLS(res, true);
  });

  fw.AddTest("Multiply two 4x4 matrices", []() -> bool {
    Matrix matrix1 = {4, 4};
    double elements1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    Matrix actual = matrix1 * matrix2;

    Matrix expected = {4, 4};
    double expected_elements[] = {20, 22, 50,  48,  44, 54, 114, 108,
                                  40, 58, 110, 102, 16, 26, 46,  42};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  fw.AddTest("Multiply a 4x4 matrix by a vector", []() -> bool {
    Matrix matrix = {4, 4};
    double elements1[] = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
    matrix.Populate(elements1, matrix.rows * matrix.cols);

    Vector vector = {1, 2, 3, 1};

    Vector actual = matrix * vector;
    Vector expected = {18, 24, 33, 1};

    return ASSERT_EQUAL_VECTORS(actual, expected);
  });

  fw.AddTest("Multiply a matrix by an identity matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements1[] = {0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
    matrix.Populate(elements1, matrix.rows * matrix.cols);

    Matrix identity_matrix = IdentityMatrix();
    Matrix actual = matrix * identity_matrix;

    return ASSERT_EQUAL_MATRICES(actual, matrix);
  });

  fw.AddTest("Transpose a 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements1[] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
    matrix.Populate(elements1, matrix.rows * matrix.cols);

    Matrix transposed_matrix = matrix.Transpose();

    Matrix expected = {4, 4};
    double elements2[] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
    matrix.Populate(elements2, matrix.rows * matrix.cols);

    return ASSERT_EQUAL_MATRICES(transposed_matrix, matrix);
  });

  fw.AddTest("Transpose an identity matrix", []() -> bool {
    Matrix identity_matrix = IdentityMatrix();
    Matrix actual = identity_matrix.Transpose();

    Matrix expected = {4, 4};
    double expected_elements[] = {1, 0, 0, 0, 0, 1, 0, 0,
                                  0, 0, 1, 0, 0, 0, 0, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  fw.AddTest("Determinant of a 2x2 matrix", []() -> bool {
    Matrix matrix = {2, 2};
    double elements[] = {1, 5, -3, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = 17.0;

    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("Submatrix of a 3x3 matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {1, 5, 0, -3, 2, 7, 0, 6, -3};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(0, 2);

    Matrix expected = {2, 2};
    double expected_elements[] = {-3, 2, 0, 6};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  fw.AddTest("Submatrix of a 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(2, 1);

    Matrix expected = {3, 3};
    double expected_elements[] = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  fw.AddTest("Minor of a 3x3 matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Minor(1, 0);
    double expected = 25.0;

    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("Cofactor of a 3x3 matrix 1", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Cofactor(0, 0);
    double expected = -12.0;

    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("Cofactor of a 3x3 matrix 2", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Cofactor(1, 0);
    double expected = -25.0;

    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("Determinant of a 3x3 matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = -196.0;

    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("Determinant of a 4x4 matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = -4071.0;

    return ASSERT_EQUAL_DOUBLES(actual, expected);
  });

  fw.AddTest("Testing a matrix for invertibility 1", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = -2120.0;

    return ASSERT_EQUAL_DOUBLES(actual, expected) &&
           ASSERT_EQUAL_BOOLS(IsEqualDouble(actual, 0.0), false);
  });

  fw.AddTest("Testing a matrix for invertibility 2", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = 0;

    return ASSERT_EQUAL_DOUBLES(actual, expected) &&
           ASSERT_EQUAL_BOOLS(IsEqualDouble(actual, 0.0), true);
  });

  fw.AddTest("Inversing a 4x4 matrix 1", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.Inverse();
    Matrix expected = {4, 4};
    double expected_elements[] = {
        116.0, 240.0,  128.0, -24.0, -430.0, -775.0, -236.0, 277.0,
        -42.0, -119.0, -28.0, 105.0, -278.0, -433.0, -160.0, 163.0,
    };

    for (int i = 0; i < 16; ++i) {
      expected_elements[i] /= 532.0;
    }

    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  fw.AddTest("Inversing a 4x4 matrix 2", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.Inverse();

    Matrix expected = {4, 4};
    double expected_elements[] = {90.0,  90.0,  165.0,  315.0,  45.0,   -72.0,
                                  -15.0, -18.0, -210.0, -210.0, -255.0, -540.0,
                                  405.0, 405.0, 450.0,  1125.0};
    for (int i = 0; i < 16; ++i) {
      expected_elements[i] /= -585.0;
    }

    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  fw.AddTest("Inversing a 4x4 matrix 3", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.Inverse();

    Matrix expected = {4, 4};
    double expected_elements[] = {-66.0, -126.0, 234.0,  -360.0, -126.0, 54.0,
                                  594.0, -540.0, -47.0,  -237.0, -177.0, 210.0,
                                  288.0, 108.0,  -432.0, 540.0};
    for (int i = 0; i < 16; ++i) {
      expected_elements[i] /= 1620.0;
    }

    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  framework.AddTest("Multiplying a product by its inverse", []() -> bool {
    Matrix matrix1 = {4, 4};
    double elements1[] = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    Matrix product = matrix1 * matrix2;

    Matrix inverse_product = matrix2.Inverse();

    Matrix actual = product * inverse_product;

    Matrix expected = matrix1;

    return ASSERT_EQUAL_MATRICES(actual, expected);
  });

  fw.RunTest();
}
