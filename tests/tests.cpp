#include <src/arr.h>
#include <src/canvas.h>
#include <src/file_io.h>
#include <src/main.h>
#include <src/matrix.h>
#include <src/pixel.h>
#include <src/point_vector.h>
#include <src/ray.h>
#include <src/str.h>
#include <src/test_suite.h>
#include <tests/tests.h>

#include <memory>
#include <string>

void RunTests(const std::string root_folder_path) {
  TestFramework fw = TestFramework{root_folder_path};

  fw.Add("Initialize array", "Arrays", []() -> bool {
    DyArray<int> arr(5);
    DyArray<int> empty_arr;
    return ASSERT_EQUAL(
        bool, arr.size == 5 && empty_arr.size == 0 && empty_arr.data == nullptr,
        true);
  });

  fw.Add("Push array elements", "Arrays", []() -> bool {
    DyArray<int> arr;
    arr.Push(1);
    bool res = ASSERT_EQUAL(bool, arr.size == 1, true) &&
               ASSERT_EQUAL(bool, arr.data[0] == 1, true);

    arr.Push(2);
    res = res && ASSERT_EQUAL(bool, arr.size == 2, true) &&
          ASSERT_EQUAL(bool, arr.data[0] == 1, true) &&
          ASSERT_EQUAL(bool, arr.data[1] == 2, true);

    arr.Push(3);
    res = res && ASSERT_EQUAL(bool, arr.size == 3, true) &&
          ASSERT_EQUAL(bool, arr.data[0] == 1, true) &&
          ASSERT_EQUAL(bool, arr.data[1] == 2, true) &&
          ASSERT_EQUAL(bool, arr.data[2] == 3, true);

    return res;
  });

  fw.Add("Remove array elements", "Arrays", []() -> bool {
    DyArray<int> arr;
    arr.Push(1);
    arr.Push(2);
    arr.Push(3);
    arr.Push(4);
    arr.Push(5);
    bool res = ASSERT_EQUAL(bool, arr.size == 5, true);

    arr.Pop();
    res = res && ASSERT_EQUAL(bool, arr.size == 4, true);
    arr.Pop();
    res = res && ASSERT_EQUAL(bool, arr.size == 3, true);
    arr.Pop();
    res = res && ASSERT_EQUAL(bool, arr.size == 2, true);
    arr.Pop();
    res = res && ASSERT_EQUAL(bool, arr.size == 1, true);
    arr.Pop();
    res = res && ASSERT_EQUAL(bool, arr.size == 0, true);

    return res;
  });

  fw.Add("Push fixed array into DyArray", "Arrays", []() -> bool {
    int elements[] = {1, 2, 3, 4, 5};
    DyArray<int> arr = {elements, 5};
    return ASSERT_EQUAL(bool, arr.size == 5 && arr.Compare(elements, 5), true);
  });

  fw.Add("Push dynamic array into DyArray", "Arrays", []() -> bool {
    size_t size = 5;
    size_t* elements = new size_t[size];
    for (size_t i = 0; i < size; ++i) {
      elements[i] = i + 1;
    }
    DyArray<size_t> arr = {elements, size};
    bool res = ASSERT_EQUAL(
        bool, arr.size == size && arr.Compare(elements, size), true);

    delete[] elements;

    return res;
  });

  fw.Add("Push shared ptr array into DyArray", "Arrays", []() -> bool {
    size_t size = 5;
    std::shared_ptr<size_t[]> elements = std::make_shared<size_t[]>(size);
    for (size_t i = 0; i < size; ++i) {
      elements[i] = i + 1;
    }
    DyArray<size_t> arr = {elements, size};
    bool res = ASSERT_EQUAL(
        bool, arr.size == size && arr.Compare(elements, size), true);

    return res;
  });

  fw.Add("Initialize string", "Strings", []() -> bool {
    String actual = String{"Hello, World!"};
    const char* expected = "Hello, World!";
    bool res = actual == expected;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Compare string lengths", "Strings", []() -> bool {
    String actual = String{"Hello, World!"};
    const char* expected = "Hello, World!";
    bool res = actual == expected && actual.length == strlen(expected);
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Copy string", "Strings", []() -> bool {
    String str = String{"Hello, World!"};
    String actual = str;
    String expected = String{"Hello, World!"};
    bool res = actual == expected;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Concatenate two strings", "Strings", []() -> bool {
    String str1 = String{"123"};
    String str2 = String{"456"};
    String actual = str1 + str2;
    String expected = String{"123456"};
    bool res = actual == expected;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Concatenate four strings", "Strings", []() -> bool {
    String str1 = String{"123"};
    String str2 = String{"456"};
    String str3 = String{"789"};
    String str4 = String{"101112"};
    String actual = str1 + str2 + str3 + str4;
    String expected = String{"123456789101112"};
    bool res = actual == expected;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Add point to vector", "Tuples", []() -> bool {
    Point left = {3, -2, 5};
    Vector right = {-2, 3, 1};
    Point actual = left + right;
    Point expected = {1, 1, 6};
    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Subtract point from point", "Tuples", []() -> bool {
    Point left = {3, 2, 1};
    Point right = {-2, 3, 1};
    Vector actual = left - right;
    Vector expected = {5, -1, 0};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Subtract vector from point", "Tuples", []() -> bool {
    Point left = {3, 2, 1};
    Vector right = {5, 6, 7};
    Point actual = left - right;
    Point expected = {-2, -4, -6};
    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Subtract vector from vector", "Tuples", []() -> bool {
    Vector left = {3, 2, 1};
    Vector right = {5, 6, 7};
    Vector actual = left - right;
    Vector expected = {-2, -4, -6};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Negate vector", "Tuples", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = -v;
    Vector expected = {-1, 2, -3};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Multiply vector by scalar", "Tuples", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v * 3.5;
    Vector expected = {3.5, -7, 10.5};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Divide vector by multiplying by scalar", "Tuples", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v * 0.5;
    Vector expected = {0.5, -1, 1.5};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Divide vector by scalar", "Tuples", []() -> bool {
    Vector v = {1, -2, 3};
    Vector actual = v / 2;
    Vector expected = {0.5, -1, 1.5};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("The magnitude of a vector 1", "Tuples", []() -> bool {
    Vector v = {1, 0, 0};
    double actual = v.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("The magnitude of a vector 2", "Tuples", []() -> bool {
    Vector v = {0, 1, 0};
    double actual = v.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("The magnitude of a vector 3", "Tuples", []() -> bool {
    Vector v = {0, 0, 1};
    double actual = v.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("The magnitude of a vector 4", "Tuples", []() -> bool {
    Vector v = {1, 2, 3};
    double actual = v.Magnitude();
    double expected = sqrt(14.0);
    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("The magnitude of a vector 5", "Tuples", []() -> bool {
    Vector v = {-1, -2, -3};
    double actual = v.Magnitude();
    double expected = sqrt(14.0);
    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("Normalize vector 1", "Tuples", []() -> bool {
    Vector v = {4, 0, 0};
    Vector actual = v.Normalize();
    Vector expected = {1, 0, 0};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Normalize vector 2", "Tuples", []() -> bool {
    Vector v = {1, 2, 3};
    Vector actual = v.Normalize();
    Vector expected = {1 / sqrt(14.0), 2 / sqrt(14.0), 3 / sqrt(14.0)};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("The magnitude of a normalized vector", "Tuples", []() -> bool {
    Vector v = {1, 2, 3};
    Vector nv = v.Normalize();
    double actual = nv.Magnitude();
    double expected = 1;
    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("The dot product (self)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    double result = v1.DotProduct(v2);
    double expected = 20;

    return ASSERT_EQUAL(double, result, expected);
  });

  fw.Add("The dot product (separate)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    double result = DotProduct(v1, v2);
    double expected = 20;

    return ASSERT_EQUAL(double, result, expected);
  });

  fw.Add("The cross product (self)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v1.CrossProduct(v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("The cross product (self, reversed)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v2.CrossProduct(v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("The cross product (separate)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v1, v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("The cross product (separate, reversed)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v2, v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Add color to color", "Colors", []() -> bool {
    Color left = {0.9, 0.6, 0.75f};
    Color right = {0.7, 0.1, 0.25f};
    Color actual = left + right;
    Color expected = {1.6, 0.7, 1};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw.Add("Subtract color from color", "Colors", []() -> bool {
    Color left = {0.9, 0.6, 0.75f};
    Color right = {0.7, 0.1, 0.25f};
    Color actual = left - right;
    Color expected = {0.2, 0.5, 0.5f};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw.Add("Multiply color by scalar", "Colors", []() -> bool {
    Color c = {0.2, 0.3, 0.4f};
    Color actual = c * 2;
    Color expected = {0.4, 0.6, 0.8f};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw.Add("Divide color by multiplying by scalar", "Colors", []() -> bool {
    Color c = {0.2, 0.3, 0.4f};
    Color actual = c * 0.5;
    Color expected = {0.1, 0.15, 0.2f};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw.Add("Divide color by scalar", "Colors", []() -> bool {
    Color c = {0.2, 0.3, 0.4f};
    Color actual = c / 2;
    Color expected = {0.1, 0.15, 0.2f};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw.Add("Multiply colors", "Colors", []() -> bool {
    Color left = {1, 0.2, 0.4};
    Color right = {0.9, 1, 0.1};
    Color actual = left * right;
    Color expected = {0.9, 0.2, 0.04};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw.Add("Create canvas", "Canvas", []() -> bool {
    Canvas canvas = {10, 20};
    size_t actual_width = canvas.width;
    size_t actual_height = canvas.height;
    size_t expected_width = 10;
    size_t expected_height = 20;
    return ASSERT_EQUAL(size_t, actual_width, expected_width) &&
           ASSERT_EQUAL(size_t, actual_height, expected_height);
  });

  fw.Add("Check all default canvas colors (black)", "Canvas", []() -> bool {
    Canvas canvas = {10, 20};
    Color black = {0, 0, 0};

    bool res = true;
    for (size_t i = 0; i < canvas.height; ++i) {
      for (size_t j = 0; j < canvas.width; ++j) {
        Pixel current_pixel = canvas.PixelAt(j, i);
        res = res && ASSERT_EQUAL(bool, current_pixel.color == black, true);
      }
    }

    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Write color of the pixel", "Canvas", []() -> bool {
    Canvas canvas = {5, 10};
    Color red = {1, 0, 0};

    size_t x = 2;
    size_t y = 3;
    canvas.WritePixelColor(x, y, red);
    Pixel pixel = canvas.PixelAt(x, y);
    Color actual_color = pixel.color;

    return ASSERT_EQUAL(Color, actual_color, red) &&
           ASSERT_EQUAL(size_t, pixel.x, x) && ASSERT_EQUAL(size_t, pixel.y, y);
  });

  fw.Add("Save canvas to PPM", "Canvas", [fw]() -> bool {
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

    std::string file_path = fw.root + "\\data\\canvas.ppm";
    bool res = canvas.SaveToPPM(file_path);

    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Load canvas from PPM", "Canvas", [fw]() -> bool {
    Canvas canvas = {0, 0};

    const std::string input_path = fw.root + "\\data\\canvas.ppm";
    bool res1 = canvas.LoadFromPPM(input_path);

    const std::string output_path = fw.root + "\\data\\canvas_output.ppm";
    bool res2 = canvas.SaveToPPM(output_path);

    bool actual = CompareFiles(input_path, output_path) && res1 && res2;
    bool expected = true;
    return ASSERT_EQUAL(bool, actual, expected);
  });

  fw.Add("Map the trajectory of projectile", "Canvas", [fw]() -> bool {
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

    std::string output_path = fw.root + "\\data\\projectile.ppm";
    bool res = canvas.SaveToPPM(output_path);

    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Initialize 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    return ASSERT_EQUAL(size_t, matrix.rows, 4) &&
           ASSERT_EQUAL(size_t, matrix.cols, 4);
  });

  fw.Add("Initialize 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix = {3, 3};
    return ASSERT_EQUAL(size_t, matrix.rows, 3) &&
           ASSERT_EQUAL(size_t, matrix.cols, 3);
  });

  fw.Add("Initialize 2x2 matrix", "Matrix", []() -> bool {
    Matrix matrix = {2, 2};
    return ASSERT_EQUAL(size_t, matrix.rows, 2) &&
           ASSERT_EQUAL(size_t, matrix.cols, 2);
  });

  fw.Add("Check 4x4 matrix values", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {1, 2,  3,  4,  5.5,  6.5f,  7.5f,  8.5f,
                         9, 10, 11, 12, 13.5, 14.5f, 15.5f, 16.5f};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL(double, matrix.At(0, 0), 1) &&
               ASSERT_EQUAL(double, matrix.At(0, 3), 4) &&
               ASSERT_EQUAL(double, matrix.At(1, 0), 5.5) &&
               ASSERT_EQUAL(double, matrix.At(1, 2), 7.5) &&
               ASSERT_EQUAL(double, matrix.At(2, 2), 11) &&
               ASSERT_EQUAL(double, matrix.At(3, 0), 13.5) &&
               ASSERT_EQUAL(double, matrix.At(3, 2), 15.5);

    return res;
  });

  fw.Add("Check 3x3 matrix values", "Matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL(double, matrix.At(0, 0), -3) &&
               ASSERT_EQUAL(double, matrix.At(1, 1), -2) &&
               ASSERT_EQUAL(double, matrix.At(2, 2), 1);

    return res;
  });

  fw.Add("Check 2x2 matrix values", "Matrix", []() -> bool {
    Matrix matrix = {2, 2};
    double elements[] = {-3, 5, 1, -2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL(double, matrix.At(0, 0), -3) &&
               ASSERT_EQUAL(double, matrix.At(0, 1), 5) &&
               ASSERT_EQUAL(double, matrix.At(1, 0), 1) &&
               ASSERT_EQUAL(double, matrix.At(1, 1), -2);

    return res;
  });

  fw.Add("Compare two equal 4x4 matrices", "Matrix", []() -> bool {
    Matrix matrix1 = {4, 4};
    double elements1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    bool res = matrix1 == matrix2;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Compare two different 4x4 matrices", "Matrix", []() -> bool {
    Matrix matrix1 = {4, 4};
    double elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    bool res = matrix1 != matrix2;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Compare two differently sized matrices", "Matrix", []() -> bool {
    Matrix matrix1 = {3, 3};
    double elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    double elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    bool res = matrix1 != matrix2;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Multiply two 4x4 matrices", "Matrix", []() -> bool {
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

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Multiply a 4x4 matrix by a 1x1 matrix", "Matrix", []() -> bool {
    Matrix matrix1 = {4, 4};
    double elements1[] = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 1};
    double elements2[] = {1, 2, 3, 1};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    Matrix actual = matrix1 * matrix2;
    Matrix expected = {4, 1};
    double expected_elements[] = {18, 24, 33, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Multiply a matrix by an identity matrix", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements1[] = {0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
    matrix.Populate(elements1, matrix.rows * matrix.cols);

    Matrix identity_matrix = Identity();
    Matrix actual = matrix * identity_matrix;

    return ASSERT_EQUAL(Matrix, actual, matrix);
  });

  fw.Add("Transpose a 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements1[] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
    matrix.Populate(elements1, matrix.rows * matrix.cols);

    Matrix transposed_matrix = matrix.Transpose();

    Matrix expected = {4, 4};
    double elements2[] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
    matrix.Populate(elements2, matrix.rows * matrix.cols);

    return ASSERT_EQUAL(Matrix, transposed_matrix, matrix);
  });

  fw.Add("Transpose an identity matrix", "Matrix", []() -> bool {
    Matrix identity_matrix = Identity();
    Matrix actual = identity_matrix.Transpose();

    Matrix expected = {4, 4};
    double expected_elements[] = {1, 0, 0, 0, 0, 1, 0, 0,
                                  0, 0, 1, 0, 0, 0, 0, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Determinant of a 2x2 matrix", "Matrix", []() -> bool {
    Matrix matrix = {2, 2};
    double elements[] = {1, 5, -3, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = 17.0;

    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("Submatrix of a 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {1, 5, 0, -3, 2, 7, 0, 6, -3};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(0, 2);

    Matrix expected = {2, 2};
    double expected_elements[] = {-3, 2, 0, 6};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Submatrix of a 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(2, 1);

    Matrix expected = {3, 3};
    double expected_elements[] = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Minor of a 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Minor(1, 0);
    double expected = 25.0;

    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("Cofactor of a 3x3 matrix 1", "Matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Cofactor(0, 0);
    double expected = -12.0;

    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("Cofactor of a 3x3 matrix 2", "Matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Cofactor(1, 0);
    double expected = -25.0;

    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("Determinant of a 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix = {3, 3};
    double elements[] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = -196.0;

    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("Determinant of a 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = -4071.0;

    return ASSERT_EQUAL(double, actual, expected);
  });

  fw.Add("Test a matrix for invertibility 1", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = -2120.0;

    return ASSERT_EQUAL(double, actual, expected) &&
           ASSERT_EQUAL(bool, IsEqualDouble(actual, 0.0), false);
  });

  fw.Add("Test a matrix for invertibility 2", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    double actual = matrix.Determinant();
    double expected = 0;

    return ASSERT_EQUAL(double, actual, expected) &&
           ASSERT_EQUAL(bool, IsEqualDouble(actual, 0.0), true);
  });

  fw.Add("Inverse a 4x4 matrix 1", "Matrix", []() -> bool {
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

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Inverse a 4x4 matrix 2", "Matrix", []() -> bool {
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

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Inverse a 4x4 matrix 3", "Matrix", []() -> bool {
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

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw.Add("Inverse of identity matrix", "Matrix", []() -> bool {
    Matrix identity_matrix = Identity();
    Matrix inverted = identity_matrix.Inverse();
    return ASSERT_EQUAL(Matrix, identity_matrix, inverted);
  });

  fw.Add("Multiply a matrix by its inverse", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix inverse = matrix.Inverse();
    Matrix identity_matrix = matrix * inverse;

    return ASSERT_EQUAL(Matrix, identity_matrix, Identity());
  });

  fw.Add("Compare inverse of transpose and vice versa", "Matrix", []() -> bool {
    Matrix matrix = {4, 4};
    double elements[] = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix inverse_transpose = matrix.Transpose().Inverse();
    Matrix transpose_inverse = matrix.Inverse().Transpose();

    return ASSERT_EQUAL(Matrix, inverse_transpose, transpose_inverse);
  });

  fw.Add("Product of point and translation matrix", "Matrix", []() -> bool {
    Matrix transform = Translate(5, -3, 2);
    Point p = {-3, 4, 5};

    Point actual = transform * p;
    Point expected = {2, 1, 7};
    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Product of point and inverse of translation", "Matrix", []() -> bool {
    Matrix transform = Translate(5, -3, 2);
    Matrix inverse = transform.Inverse();
    Point p = {-3, 4, 5};

    Point actual = inverse * p;
    Point expected = {-8, 7, 3};
    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Product of vector and a translation matrix", "Matrix", []() -> bool {
    Matrix transform = Translate(5, -3, 2);
    Vector v = {-3, 4, 5};

    Vector actual = transform * v;
    Vector expected = v;

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("A scaling matrix applied to a point", "Matrix", []() -> bool {
    Matrix transform = Scale(2, 3, 4);
    Point p = {-4, 6, 8};

    Point actual = transform * p;
    Point expected = {-8, 18, 32};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("A scaling matrix applied to a vector", "Matrix", []() -> bool {
    Matrix transform = Scale(2, 3, 4);
    Vector v = {-4, 6, 8};

    Vector actual = transform * v;
    Vector expected = {-8, 18, 32};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Product of the inverse and a scaling matrix", "Matrix", []() -> bool {
    Matrix transform = Scale(2, 3, 4);
    Matrix inverse = transform.Inverse();
    Vector v = {-4, 6, 8};

    Vector actual = inverse * v;
    Vector expected = {-2, 2, 2};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw.Add("Reflect a point", "Matrix", []() -> bool {
    Matrix transform = Scale(-1, 1, 1);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {-2, 3, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Rotate a point around the x axis", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateX(PI / 4);
    Matrix full_quarter = RotateX(PI / 2);

    Point actual1 = half_quarter * p;
    Point actual2 = full_quarter * p;
    Point expected1 = {0, sqrt(2) / 2, sqrt(2) / 2};
    Point expected2 = {0, 0, 1};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2);
  });

  fw.Add("Opposite inverse of X-rotation", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateX(PI / 4);
    Matrix inverse = half_quarter.Inverse();

    Point actual = inverse * p;
    Point expected = {0, sqrt(2) / 2, -sqrt(2) / 2};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Rotate a point around the Y axis", "Matrix", []() -> bool {
    Point p = {0, 0, 1};
    Matrix half_quarter = RotateY(PI / 4);
    Matrix full_quarter = RotateY(PI / 2);

    Point actual1 = half_quarter * p;
    Point actual2 = full_quarter * p;
    Point expected1 = {sqrt(2) / 2, 0, sqrt(2) / 2};
    Point expected2 = {1, 0, 0};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2);
  });

  fw.Add("Opposite inverse of Y-rotation", "Matrix", []() -> bool {
    Point p = {0, 0, 1};
    Matrix half_quarter = RotateY(PI / 4);
    Matrix inverse = half_quarter.Inverse();

    Point actual = inverse * p;
    Point expected = {-sqrt(2) / 2, 0, sqrt(2) / 2};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Rotate a point around the Z axis", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateZ(PI / 4);
    Matrix full_quarter = RotateZ(PI / 2);

    Point actual1 = half_quarter * p;
    Point actual2 = full_quarter * p;
    Point expected1 = {-sqrt(2) / 2, sqrt(2) / 2, 0};
    Point expected2 = {-1, 0, 0};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2);
  });

  fw.Add("Opposite inverse of Z-rotation", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateZ(PI / 4);
    Matrix inverse = half_quarter.Inverse();

    Point actual = inverse * p;
    Point expected = {sqrt(2) / 2, sqrt(2) / 2, 0};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Shear X in proportion to Y", "Matrix", []() -> bool {
    Matrix transform = Shear(XY);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {5, 3, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Shear X in proportion to Z", "Matrix", []() -> bool {
    Matrix transform = Shear(XZ);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {6, 3, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Shear Y in proportion to X", "Matrix", []() -> bool {
    Matrix transform = Shear(YX);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {2, 5, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Shear Y in proportion to Z", "Matrix", []() -> bool {
    Matrix transform = Shear(YZ);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {2, 7, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Shear Z in proportion to X", "Matrix", []() -> bool {
    Matrix transform = Shear(ZX);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {2, 3, 6};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Shear Z in proportion to Y", "Matrix", []() -> bool {
    Matrix transform = Shear(ZY);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {2, 3, 7};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Tranformation sequence", "Matrix", []() -> bool {
    Point p = {1, 0, 1};

    Matrix rotate_x_tf = RotateX(PI / 2);
    Matrix scale_tf = Scale(5, 5, 5);
    Matrix translate_tf = Translate(10, 5, 7);

    Point actual1 = rotate_x_tf * p;
    Point expected1 = {1, -1, 0};

    Point actual2 = scale_tf * actual1;
    Point expected2 = {5, -5, 0};

    Point actual3 = translate_tf * actual2;
    Point expected3 = {15, 0, 7};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2) &&
           ASSERT_EQUAL(Point, actual3, expected3);
  });

  fw.Add("Tranformation chain", "Matrix", []() -> bool {
    Point p = {1, 0, 1};
    Matrix transform = Translate(10, 5, 7) * Scale(5, 5, 5) * RotateX(PI / 2);

    Point actual = transform * p;
    Point expected = {15, 0, 7};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Tranformation chain (fluid)", "Matrix", []() -> bool {
    Point p = {1, 0, 1};

    Matrix transform =
        Identity().RotateX(PI / 2).Scale(5, 5, 5).Translate(10, 5, 7);

    Point actual = transform * p;
    Point expected = {15, 0, 7};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw.Add("Clock", "Matrix", [fw]() -> bool {
    Canvas canvas = {600, 600};
    size_t radius = (canvas.width - 100) / 2;
    Point origin = {canvas.width / 2.0, 0, canvas.height / 2.0};
    Color green = {0, 1, 0};

    size_t resolution = 12;

    std::unique_ptr<Point[]> points = std::make_unique<Point[]>(resolution);

    Point start = {0, 0, 1};
    double turn = PI / (static_cast<double>(resolution) / 2);
    for (size_t i = 0; i < resolution; ++i) {
      double radians = i * turn;
      points[i] = RotateY(radians) * start;

      size_t pos_x = static_cast<size_t>(origin.x + points[i].x * radius);
      size_t pos_y = static_cast<size_t>(origin.z + points[i].z * radius);
      canvas.WritePixelColor(pos_x, pos_y, green);
    }

    std::string output_path = fw.root + "\\data\\clock.ppm";
    bool res = canvas.SaveToPPM(output_path);

    return ASSERT_EQUAL(bool, res, true);
  });

  fw.Add("Create and query a ray", "Rays", []() -> bool {
    Point origin = {1, 2, 3};
    Vector direction = {4, 5, 6};

    Ray ray1 = {origin, direction};
    Ray ray2;
    ray2.origin = origin;
    ray2.direction = direction;

    return ASSERT_EQUAL(Point, ray1.origin, origin) &&
           ASSERT_EQUAL(Vector, ray1.direction, direction) &&
           ASSERT_EQUAL(Ray, ray1, ray2);
  });

  fw.Add("Compute a point from a distance", "Rays", []() -> bool {
    Ray ray = {{2, 3, 4}, {1, 0, 0}};

    Point actual1 = ray.Position(0);
    Point expected1 = {2, 3, 4};

    Point actual2 = ray.Position(1);
    Point expected2 = {3, 3, 4};

    Point actual3 = ray.Position(-1);
    Point expected3 = {1, 3, 4};

    Point actual4 = ray.Position(2.5);
    Point expected4 = {4.5, 3, 4};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2) &&
           ASSERT_EQUAL(Point, actual3, expected3) &&
           ASSERT_EQUAL(Point, actual4, expected4);
  });

  fw.Add("Hit a sphere at two points with a ray", "Rays", []() -> bool {
    Ray ray = {{0, 0, -5}, {0, 0, 1}};
    Sphere sphere;
    Hits xs = ray.Intersect(sphere);

    return ASSERT_EQUAL(size_t, xs.count, 2) &&
           ASSERT_EQUAL(double, xs[0].t, 4.0) &&
           ASSERT_EQUAL(double, xs[1].t, 6.0);
  });

  fw.Add("Hit a sphere at a tangent with a ray", "Rays", []() -> bool {
    Ray ray = {{0, 1, -5}, {0, 0, 1}};
    Sphere sphere;
    Hits xs = ray.Intersect(sphere);

    return ASSERT_EQUAL(size_t, xs.count, 1) &&
           ASSERT_EQUAL(double, xs[0].t, 5.0);
  });

  fw.Add("Miss a sphere with a ray", "Rays", []() -> bool {
    Ray ray = {{0, 2, -5}, {0, 0, 1}};
    Sphere sphere;
    Hits xs = ray.Intersect(sphere);

    return ASSERT_EQUAL(size_t, xs.count, 0);
  });

  fw.Add("Hit a sphere with a ray at its center", "Rays", []() -> bool {
    Ray ray = {{0, 0, 0}, {0, 0, 1}};
    Sphere sphere;
    Hits xs = ray.Intersect(sphere);

    return ASSERT_EQUAL(size_t, xs.count, 2) &&
           ASSERT_EQUAL(double, xs[0].t, -1.0) &&
           ASSERT_EQUAL(double, xs[1].t, 1.0);
  });

  fw.Add("Hit a sphere with a ray behind it", "Rays", []() -> bool {
    Ray ray = {{0, 0, 5}, {0, 0, 1}};
    Sphere sphere;
    Hits xs = ray.Intersect(sphere);

    return ASSERT_EQUAL(size_t, xs.count, 2) &&
           ASSERT_EQUAL(double, xs[0].t, -6.0) &&
           ASSERT_EQUAL(double, xs[1].t, -4.0);
  });

  fw.Add("Initialize hit and hits", "Rays", []() -> bool {
    Sphere sphere;
    Hit hit = {3.5, {SPHERE, &sphere}};

    Hits xs;
    xs.Push(&hit);

    Hits xs_copy = xs;

    return ASSERT_EQUAL(double, hit.t, 3.5) &&
           ASSERT_EQUAL(Sphere, *reinterpret_cast<Sphere*>(hit.object.data),
                        sphere) &&
           ASSERT_EQUAL(Hits, xs, xs_copy) &&
           ASSERT_EQUAL(size_t, xs.count, 1) &&
           ASSERT_EQUAL(double, xs.hits[0].t, 3.5);
  });

  fw.Add("Aggregate hits", "Rays", []() -> bool {
    Sphere sphere;
    Hit hit1 = {1, {SPHERE, &sphere}};
    Hit hit2 = {2, {SPHERE, &sphere}};
    Hit hits[] = {hit1, hit2};

    Hits xs = Aggregate(2, hits);

    return ASSERT_EQUAL(size_t, xs.count, 2) &&
           ASSERT_EQUAL(double, xs[0].t, 1.0) &&
           ASSERT_EQUAL(double, xs[1].t, 2.0);
  });

  fw.RunTests();
}
