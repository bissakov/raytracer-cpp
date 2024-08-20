#include <core/arr.h>
#include <core/file_io.h>
#include <core/test_suite.h>
#include <core/utils.h>
#include <geometry/matrix.h>
#include <geometry/ray.h>
#include <geometry/vector.h>
#include <render/canvas.h>
#include <render/color.h>
#include <render/light.h>
#include <render/material.h>
#include <tests/tests.h>

#include <memory>

static inline void TestArray(TestFramework* fw) {
  fw->Run("Initialize array", "Arrays", []() -> bool {
    DyArray<int> arr(5);
    DyArray<int> empty_arr;
    return ASSERT_EQUAL(
        bool, arr.size == 5 && empty_arr.size == 0 && empty_arr.data == nullptr,
        true);
  });

  fw->Run("Push array elements", "Arrays", []() -> bool {
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

  fw->Run("Remove array elements", "Arrays", []() -> bool {
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

  fw->Run("Push fixed array into DyArray", "Arrays", []() -> bool {
    int elements[]{1, 2, 3, 4, 5};
    DyArray<int> arr{elements, 5};
    return ASSERT_EQUAL(bool, arr.size == 5 && arr.Compare(elements, 5), true);
  });

  fw->Run("Push dynamic array into DyArray", "Arrays", []() -> bool {
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

  fw->Run("Push shared ptr array into DyArray", "Arrays", []() -> bool {
    size_t size = 5;
    std::shared_ptr<size_t[]> elements = std::make_shared<size_t[]>(size);
    for (size_t i = 0; i < size; ++i) {
      elements[i] = i + 1;
    }
    DyArray<size_t> arr = {elements, size};

    return ASSERT_EQUAL(size_t, arr.size, size) &&
           ASSERT_EQUAL(bool, arr.Compare(elements, size), true);
  });
}

static inline void TestTuple(TestFramework* fw) {
  fw->Run("Add point to vector", "Tuples", []() -> bool {
    Point left{3, -2, 5};
    Vector right{-2, 3, 1};
    Point actual{left + right};
    Point expected{1, 1, 6};
    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Subtract point from point", "Tuples", []() -> bool {
    Point left{3, 2, 1};
    Point right{-2, 3, 1};
    Vector actual{left - right};
    Vector expected{5, -1, 0};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Subtract vector from point", "Tuples", []() -> bool {
    Point left{3, 2, 1};
    Vector right{5, 6, 7};
    Point actual{left - right};
    Point expected{-2, -4, -6};
    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Subtract vector from vector", "Tuples", []() -> bool {
    Vector left{3, 2, 1};
    Vector right{5, 6, 7};
    Vector actual{left - right};
    Vector expected{-2, -4, -6};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Negate vector", "Tuples", []() -> bool {
    Vector v{1, -2, 3};
    Vector actual{-v};
    Vector expected{-1, 2, -3};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Multiply vector by scalar", "Tuples", []() -> bool {
    Vector v{1, -2, 3};
    Vector actual{v * 3.5};
    Vector expected{3.5, -7, 10.5};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Divide vector by multiplying by scalar", "Tuples", []() -> bool {
    Vector v{1, -2, 3};
    Vector actual{v * 0.5};
    Vector expected{0.5, -1, 1.5};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Divide vector by scalar", "Tuples", []() -> bool {
    Vector v{1, -2, 3};
    Vector actual{v / 2};
    Vector expected{0.5, -1, 1.5};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("The magnitude of a vector 1", "Tuples", []() -> bool {
    Vector v{1, 0, 0};
    float actual = v.Magnitude();
    float expected = 1;
    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("The magnitude of a vector 2", "Tuples", []() -> bool {
    Vector v{0, 1, 0};
    float actual = v.Magnitude();
    float expected = 1;
    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("The magnitude of a vector 3", "Tuples", []() -> bool {
    Vector v{0, 0, 1};
    float actual = v.Magnitude();
    float expected = 1;
    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("The magnitude of a vector 4", "Tuples", []() -> bool {
    Vector v = {1, 2, 3};
    float actual = v.Magnitude();
    float expected = sqrt(14.F);
    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("The magnitude of a vector 5", "Tuples", []() -> bool {
    Vector v = {-1, -2, -3};
    float actual = v.Magnitude();
    float expected = sqrt(14.F);
    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("Normalize vector 1", "Tuples", []() -> bool {
    Vector v = {4, 0, 0};
    Vector actual = v.Normalize();
    Vector expected = {1, 0, 0};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Normalize vector 2", "Tuples", []() -> bool {
    Vector v = {1, 2, 3};
    Vector actual = v.Normalize();
    Vector expected = {1 / sqrt(14.F), 2 / sqrt(14.F), 3 / sqrt(14.F)};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("The magnitude of a normalized vector", "Tuples", []() -> bool {
    Vector v = {1, 2, 3};
    Vector nv = v.Normalize();
    float actual = nv.Magnitude();
    float expected = 1.F;

    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("The dot product (self)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    float result = v1.DotProduct(v2);
    float expected = 20;

    return ASSERT_EQUAL_FLOAT(result, expected);
  });

  fw->Run("The dot product (separate)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    float result = DotProduct(v1, v2);
    float expected = 20;

    return ASSERT_EQUAL_FLOAT(result, expected);
  });

  fw->Run("The cross product (self)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v1.CrossProduct(v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("The cross product (self, reversed)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = v2.CrossProduct(v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("The cross product (separate)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v1, v2);
    Vector expected = {-1, 2, -1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("The cross product (separate, reversed)", "Tuples", []() -> bool {
    Vector v1 = {1, 2, 3};
    Vector v2 = {2, 3, 4};
    Vector actual = CrossProduct(v2, v1);
    Vector expected = {1, -2, 1};
    return ASSERT_EQUAL(Vector, actual, expected);
  });
}

static inline void TestColor(TestFramework* fw) {
  fw->Run("Add color to color", "Colors", []() -> bool {
    Color left{0.9F, 0.6F, 0.75F};
    Color right{0.7F, 0.1F, 0.25F};
    Color actual{left + right};
    Color expected{1.6F, 0.7F, 1};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Subtract color from color", "Colors", []() -> bool {
    Color left{0.9F, 0.6F, 0.75F};
    Color right{0.7F, 0.1F, 0.25F};
    Color actual{left - right};
    Color expected{0.2F, 0.5F, 0.5F};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Multiply color by scalar", "Colors", []() -> bool {
    Color c{0.2F, 0.3F, 0.4F};
    Color actual{c * 2.F};
    Color expected{0.4F, 0.6F, 0.8F};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Divide color by multiplying by scalar", "Colors", []() -> bool {
    Color c{0.2F, 0.3F, 0.4F};
    Color actual{c * 0.5F};
    Color expected{0.1F, 0.15F, 0.2F};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Divide color by scalar", "Colors", []() -> bool {
    Color c{0.2F, 0.3F, 0.4F};
    Color actual{c / 2.F};
    Color expected{0.1F, 0.15F, 0.2F};
    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Multiply colors", "Colors", []() -> bool {
    Color left{1, 0.2F, 0.4F};
    Color right{0.9F, 1, 0.1F};
    Color actual{left * right};
    Color expected{0.9F, 0.2F, 0.04F};
    return ASSERT_EQUAL(Color, actual, expected);
  });
}

static inline void TestCanvas(TestFramework* fw) {
  fw->Run("Create canvas", "Canvas", []() -> bool {
    Canvas canvas{10, 20};
    size_t actual_width = canvas.width;
    size_t actual_height = canvas.height;
    size_t expected_width = 10;
    size_t expected_height = 20;
    return ASSERT_EQUAL(size_t, actual_width, expected_width) &&
           ASSERT_EQUAL(size_t, actual_height, expected_height);
  });

  fw->Run("Check all default canvas colors (black)", "Canvas", []() -> bool {
    Canvas canvas{10, 20};
    Color black{0, 0, 0};

    bool res = true;
    for (size_t i = 0; i < canvas.height; ++i) {
      for (size_t j = 0; j < canvas.width; ++j) {
        Color current_color = canvas.ColorAt(j, i);
        res = res && ASSERT_EQUAL(bool, current_color == black, true);
      }
    }

    return ASSERT_EQUAL(bool, res, true);
  });

  fw->Run("Write color of the pixel", "Canvas", []() -> bool {
    Canvas canvas{5, 10};
    Color red{1, 0, 0};

    size_t x = 2;
    size_t y = 3;
    canvas.WriteColor(x, y, red);
    Color color = canvas.ColorAt(x, y);

    return ASSERT_EQUAL(Color, color, red);
  });

  fw->Run("Save canvas to PPM", "Canvas", [fw]() -> bool {
    Canvas canvas{500, 300};

    Color blue{0, 0.34F, 0.72F};
    Color yellow{1, 0.85F, 0};

    size_t stripe_thickness = 20;

    for (size_t j = 0; j < canvas.height; ++j) {
      for (size_t i = 0; i < canvas.width; ++i) {
        if ((i / stripe_thickness + j / stripe_thickness) % 2 == 0) {
          canvas.WriteColor(i, j, blue);
        } else {
          canvas.WriteColor(i, j, yellow);
        }
      }
    }

    Path file_path = Join(fw->root, "/data/canvas.ppm");
    bool res = canvas.SaveToPPM(file_path);

    return ASSERT_EQUAL(bool, res, true);
  });

  fw->Run("Load canvas from PPM", "Canvas", [fw]() -> bool {
    Canvas canvas{0, 0};

    Path input_path = Join(fw->root, "/data/canvas.ppm");
    bool res1 = canvas.LoadFromPPM(input_path);

    Path output_path = Join(fw->root, "/data/canvas_output.ppm");
    bool res2 = canvas.SaveToPPM(output_path);

    bool actual =
        CompareFiles(input_path.value, output_path.value) && res1 && res2;
    bool expected = true;
    return ASSERT_EQUAL(bool, actual, expected);
  });

  fw->Run("Map the trajectory of projectile", "Canvas", [fw]() -> bool {
    Canvas canvas{900, 550};

    Projectile proj{{0, 1, 0}, {1, 1.8F, 0}};
    proj.velocity = proj.velocity.Normalize() * 11.25F;

    Environment env{{0, -0.1F, 0}, {-0.01F, 0, 0}};

    Color red{1, 0, 0};

    while (proj.position.y > 0) {
      size_t pos_x = static_cast<size_t>(floor(proj.position.x));
      size_t pos_y = static_cast<size_t>(floor(proj.position.y));
      pos_y = static_cast<size_t>(
          abs(static_cast<float>(canvas.height) - floor(proj.position.y)));

      if (canvas.IsInRange(pos_x, pos_y)) {
        canvas.WriteColor(pos_x, pos_y, red);
      }

      proj.position = proj.position + proj.velocity;
      proj.velocity = proj.velocity + env.gravity + env.wind;
    }

    Path output_path = Join(fw->root, "/data/projectile.ppm");
    bool res = canvas.SaveToPPM(output_path);

    return ASSERT_EQUAL(bool, res, true);
  });
}

static inline void TestMatrix(TestFramework* fw) {
  fw->Run("Initialize 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    return ASSERT_EQUAL(size_t, matrix.rows, 4) &&
           ASSERT_EQUAL(size_t, matrix.cols, 4);
  });

  fw->Run("Initialize 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix{3, 3};
    return ASSERT_EQUAL(size_t, matrix.rows, 3) &&
           ASSERT_EQUAL(size_t, matrix.cols, 3);
  });

  fw->Run("Initialize 2x2 matrix", "Matrix", []() -> bool {
    Matrix matrix{2, 2};
    return ASSERT_EQUAL(size_t, matrix.rows, 2) &&
           ASSERT_EQUAL(size_t, matrix.cols, 2);
  });

  fw->Run("Check 4x4 matrix values", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {1, 2,  3,  4,  5.5,  6.5F,  7.5F,  8.5F,
                        9, 10, 11, 12, 13.5, 14.5F, 15.5F, 16.5F};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL_FLOAT(matrix.At(0, 0), 1) &&
               ASSERT_EQUAL_FLOAT(matrix.At(0, 3), 4) &&
               ASSERT_EQUAL_FLOAT(matrix.At(1, 0), 5.5) &&
               ASSERT_EQUAL_FLOAT(matrix.At(1, 2), 7.5) &&
               ASSERT_EQUAL_FLOAT(matrix.At(2, 2), 11) &&
               ASSERT_EQUAL_FLOAT(matrix.At(3, 0), 13.5) &&
               ASSERT_EQUAL_FLOAT(matrix.At(3, 2), 15.5);

    return res;
  });

  fw->Run("Check 3x3 matrix values", "Matrix", []() -> bool {
    Matrix matrix{3, 3};
    float elements[] = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL_FLOAT(matrix.At(0, 0), -3) &&
               ASSERT_EQUAL_FLOAT(matrix.At(1, 1), -2) &&
               ASSERT_EQUAL_FLOAT(matrix.At(2, 2), 1);

    return res;
  });

  fw->Run("Check 2x2 matrix values", "Matrix", []() -> bool {
    Matrix matrix{2, 2};
    float elements[] = {-3, 5, 1, -2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    bool res = ASSERT_EQUAL_FLOAT(matrix.At(0, 0), -3) &&
               ASSERT_EQUAL_FLOAT(matrix.At(0, 1), 5) &&
               ASSERT_EQUAL_FLOAT(matrix.At(1, 0), 1) &&
               ASSERT_EQUAL_FLOAT(matrix.At(1, 1), -2);

    return res;
  });

  fw->Run("Compare two equal 4x4 matrices", "Matrix", []() -> bool {
    Matrix matrix1 = {4, 4};
    float elements1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    float elements2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    return ASSERT_EQUAL(Matrix, matrix1, matrix2);
  });

  fw->Run("Compare two different 4x4 matrices", "Matrix", []() -> bool {
    Matrix matrix1 = {4, 4};
    float elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    float elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    return ASSERT_NOT_EQUAL(Matrix, matrix1, matrix2);
  });

  fw->Run("Compare two differently sized matrices", "Matrix", []() -> bool {
    Matrix matrix1 = {3, 3};
    float elements1[] = {1, 2, 3, 2, 5, 6, 7, 8, 9};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    float elements2[] = {1, 2, 3, 4, 5, 6, 9, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    bool res = matrix1 != matrix2;
    return ASSERT_EQUAL(bool, res, true);
  });

  fw->Run("Multiply two 4x4 matrices", "Matrix", []() -> bool {
    Matrix matrix1 = {4, 4};
    float elements1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 4};
    float elements2[] = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    Matrix actual = matrix1 * matrix2;

    Matrix expected = {4, 4};
    float expected_elements[] = {20, 22, 50,  48,  44, 54, 114, 108,
                                 40, 58, 110, 102, 16, 26, 46,  42};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Multiply a 4x4 matrix by a 1x1 matrix", "Matrix", []() -> bool {
    Matrix matrix1 = {4, 4};
    float elements1[] = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
    matrix1.Populate(elements1, matrix1.rows * matrix1.cols);

    Matrix matrix2 = {4, 1};
    float elements2[] = {1, 2, 3, 1};
    matrix2.Populate(elements2, matrix2.rows * matrix2.cols);

    Matrix actual = matrix1 * matrix2;
    Matrix expected = {4, 1};
    float expected_elements[] = {18, 24, 33, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Multiply a matrix by an identity matrix", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements1[] = {0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32};
    matrix.Populate(elements1, matrix.rows * matrix.cols);

    Matrix identity_matrix{Identity()};
    Matrix actual = matrix * identity_matrix;

    return ASSERT_EQUAL(Matrix, actual, matrix);
  });

  fw->Run("Transpose a 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements1[] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
    matrix.Populate(elements1, matrix.rows * matrix.cols);

    Matrix transposed_matrix = matrix.Transpose();

    Matrix expected = {4, 4};
    float elements2[] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
    matrix.Populate(elements2, matrix.rows * matrix.cols);

    return ASSERT_EQUAL(Matrix, transposed_matrix, matrix);
  });

  fw->Run("Transpose an identity matrix", "Matrix", []() -> bool {
    Matrix identity_matrix{Identity()};
    Matrix actual = identity_matrix.Transpose();

    Matrix expected = {4, 4};
    float expected_elements[] = {1, 0, 0, 0, 0, 1, 0, 0,
                                 0, 0, 1, 0, 0, 0, 0, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Determinant of a 2x2 matrix", "Matrix", []() -> bool {
    Matrix matrix{2, 2};
    float elements[] = {1, 5, -3, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Determinant();
    float expected = 17.F;

    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("Submatrix of a 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix{3, 3};
    float elements[] = {1, 5, 0, -3, 2, 7, 0, 6, -3};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(0, 2);

    Matrix expected = {2, 2};
    float expected_elements[] = {-3, 2, 0, 6};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Submatrix of a 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.SubMatrix(2, 1);

    Matrix expected = {3, 3};
    float expected_elements[] = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Minor of a 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix{3, 3};
    float elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Minor(1, 0);
    float expected = 25.F;

    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("Cofactor of a 3x3 matrix 1", "Matrix", []() -> bool {
    Matrix matrix{3, 3};
    float elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Cofactor(0, 0);
    float expected = -12.F;

    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("Cofactor of a 3x3 matrix 2", "Matrix", []() -> bool {
    Matrix matrix{3, 3};
    float elements[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Cofactor(1, 0);
    float expected = -25.F;

    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("Determinant of a 3x3 matrix", "Matrix", []() -> bool {
    Matrix matrix{3, 3};
    float elements[] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Determinant();
    float expected = -196.F;

    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("Determinant of a 4x4 matrix", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Determinant();
    float expected = -4071.F;

    return ASSERT_EQUAL_FLOAT(actual, expected);
  });

  fw->Run("Test a matrix for invertibility 1", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Determinant();
    float expected = -2120.F;

    return ASSERT_EQUAL_FLOAT(actual, expected) &&
           ASSERT_EQUAL(bool, IsEqualFloat(actual, 0.F), false);
  });

  fw->Run("Test a matrix for invertibility 2", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    float actual = matrix.Determinant();
    float expected = 0.F;

    return ASSERT_EQUAL_FLOAT(actual, expected) &&
           ASSERT_EQUAL(bool, IsEqualFloat(actual, 0.F), true);
  });

  fw->Run("Inverse a 4x4 matrix 1", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.Inverse();
    Matrix expected = {4, 4};
    float expected_elements[] = {
        116.F, 240.F,  128.F, -24.F, -430.F, -775.F, -236.F, 277.F,
        -42.F, -119.F, -28.F, 105.F, -278.F, -433.F, -160.F, 163.F,
    };

    for (int i = 0; i < 16; ++i) {
      expected_elements[i] /= 532.F;
    }

    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Inverse a 4x4 matrix 2", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.Inverse();

    Matrix expected = {4, 4};
    float expected_elements[] = {90.F,  90.F,  165.F,  315.F,  45.F,   -72.F,
                                 -15.F, -18.F, -210.F, -210.F, -255.F, -540.F,
                                 405.F, 405.F, 450.F,  1125.F};
    for (int i = 0; i < 16; ++i) {
      expected_elements[i] /= -585.F;
    }

    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Inverse a 4x4 matrix 3", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix actual = matrix.Inverse();

    Matrix expected = {4, 4};
    float expected_elements[] = {-66.F, -126.F, 234.F,  -360.F, -126.F, 54.F,
                                 594.F, -540.F, -47.F,  -237.F, -177.F, 210.F,
                                 288.F, 108.F,  -432.F, 540.F};
    for (int i = 0; i < 16; ++i) {
      expected_elements[i] /= 1620.F;
    }

    expected.Populate(expected_elements, expected.rows * expected.cols);

    return ASSERT_EQUAL(Matrix, actual, expected);
  });

  fw->Run("Inverse of identity matrix", "Matrix", []() -> bool {
    Matrix identity_matrix{Identity()};
    Matrix inverted = identity_matrix.Inverse();
    return ASSERT_EQUAL(Matrix, identity_matrix, inverted);
  });

  fw->Run("Multiply a matrix by its inverse", "Matrix", []() -> bool {
    Matrix matrix{4, 4};
    float elements[] = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
    matrix.Populate(elements, matrix.rows * matrix.cols);

    Matrix inverse = matrix.Inverse();
    Matrix identity_matrix = matrix * inverse;

    return ASSERT_EQUAL(Matrix, identity_matrix, Identity());
  });

  fw->Run("Compare inverse of transpose and vice versa", "Matrix",
          []() -> bool {
            Matrix matrix{4, 4};
            float elements[] = {9,  3, 0, 9, -5, -2, -6, -3,
                                -4, 9, 6, 4, -7, 6,  6,  2};
            matrix.Populate(elements, matrix.rows * matrix.cols);

            Matrix inverse_transpose = matrix.Transpose().Inverse();
            Matrix transpose_inverse = matrix.Inverse().Transpose();

            return ASSERT_EQUAL(Matrix, inverse_transpose, transpose_inverse);
          });

  fw->Run("Product of point and translation matrix", "Matrix", []() -> bool {
    Matrix transform = Translate(5, -3, 2);
    Point p = {-3, 4, 5};

    Point actual = transform * p;
    Point expected = {2, 1, 7};
    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Product of point and inverse of translation", "Matrix",
          []() -> bool {
            Matrix transform = Translate(5, -3, 2);
            Matrix inverse = transform.Inverse();
            Point p = {-3, 4, 5};

            Point actual = inverse * p;
            Point expected = {-8, 7, 3};
            return ASSERT_EQUAL(Point, actual, expected);
          });

  fw->Run("Product of vector and a translation matrix", "Matrix", []() -> bool {
    Matrix transform = Translate(5, -3, 2);
    Vector v = {-3, 4, 5};

    Vector actual = transform * v;
    Vector expected = v;

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("A scaling matrix applied to a point", "Matrix", []() -> bool {
    Matrix transform = Scale(2, 3, 4);
    Point p = {-4, 6, 8};

    Point actual = transform * p;
    Point expected = {-8, 18, 32};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("A scaling matrix applied to a vector", "Matrix", []() -> bool {
    Matrix transform = Scale(2, 3, 4);
    Vector v = {-4, 6, 8};

    Vector actual = transform * v;
    Vector expected = {-8, 18, 32};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Product of the inverse and a scaling matrix", "Matrix",
          []() -> bool {
            Matrix transform{Scale(2, 3, 4)};
            Matrix inverse{transform.Inverse()};
            Vector v{-4, 6, 8};

            Vector actual{inverse * v};
            Vector expected{-2, 2, 2};

            return ASSERT_EQUAL(Vector, actual, expected);
          });

  fw->Run("Reflect a point", "Matrix", []() -> bool {
    Matrix transform = Scale(-1, 1, 1);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {-2, 3, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Rotate a point around the x axis", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateX(static_cast<float>(PI) / 4.F);
    Matrix full_quarter = RotateX(static_cast<float>(PI) / 2.F);

    Point actual1 = half_quarter * p;
    Point actual2 = full_quarter * p;
    Point expected1 = {0, sqrt(2.F) / 2.F, sqrt(2.F) / 2.F};
    Point expected2 = {0, 0, 1};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2);
  });

  fw->Run("Opposite inverse of X-rotation", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateX(static_cast<float>(PI) / 4.F);
    Matrix inverse = half_quarter.Inverse();

    Point actual = inverse * p;
    Point expected = {0, sqrt(2.F) / 2.F, -sqrt(2.F) / 2.F};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Rotate a point around the Y axis", "Matrix", []() -> bool {
    Point p = {0, 0, 1};
    Matrix half_quarter = RotateY(static_cast<float>(PI) / 4.F);
    Matrix full_quarter = RotateY(static_cast<float>(PI) / 2.F);

    Point actual1 = half_quarter * p;
    Point actual2 = full_quarter * p;
    Point expected1 = {sqrt(2.F) / 2.F, 0, sqrt(2.F) / 2.F};
    Point expected2 = {1, 0, 0};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2);
  });

  fw->Run("Opposite inverse of Y-rotation", "Matrix", []() -> bool {
    Point p = {0, 0, 1};
    Matrix half_quarter = RotateY(static_cast<float>(PI) / 4.F);
    Matrix inverse = half_quarter.Inverse();

    Point actual = inverse * p;
    Point expected = {-sqrt(2.F) / 2.F, 0, sqrt(2.F) / 2.F};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Rotate a point around the Z axis", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateZ(static_cast<float>(PI) / 4.F);
    Matrix full_quarter = RotateZ(static_cast<float>(PI) / 2.F);

    Point actual1 = half_quarter * p;
    Point actual2 = full_quarter * p;
    Point expected1 = {-sqrt(2.F) / 2.F, sqrt(2.F) / 2.F, 0};
    Point expected2 = {-1, 0, 0};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2);
  });

  fw->Run("Opposite inverse of Z-rotation", "Matrix", []() -> bool {
    Point p = {0, 1, 0};
    Matrix half_quarter = RotateZ(static_cast<float>(PI) / 4.F);
    Matrix inverse = half_quarter.Inverse();

    Point actual = inverse * p;
    Point expected = {sqrt(2.F) / 2.F, sqrt(2.F) / 2.F, 0};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Shear X in proportion to Y", "Matrix", []() -> bool {
    Matrix transform = Shear(XY);
    Point p = {2, 3, 4};

    Point actual = transform * p;
    Point expected = {5, 3, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Shear X in proportion to Z", "Matrix", []() -> bool {
    Matrix transform = Shear(XZ);
    Point p{2, 3, 4};

    Point actual = transform * p;
    Point expected{6, 3, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Shear Y in proportion to X", "Matrix", []() -> bool {
    Matrix transform = Shear(YX);
    Point p{2, 3, 4};

    Point actual = transform * p;
    Point expected{2, 5, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Shear Y in proportion to Z", "Matrix", []() -> bool {
    Matrix transform = Shear(YZ);
    Point p{2, 3, 4};

    Point actual = transform * p;
    Point expected{2, 7, 4};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Shear Z in proportion to X", "Matrix", []() -> bool {
    Matrix transform = Shear(ZX);
    Point p{2, 3, 4};

    Point actual = transform * p;
    Point expected{2, 3, 6};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Shear Z in proportion to Y", "Matrix", []() -> bool {
    Matrix transform = Shear(ZY);
    Point p{2, 3, 4};

    Point actual = transform * p;
    Point expected{2, 3, 7};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Tranformation sequence", "Matrix", []() -> bool {
    Point p{1, 0, 1};

    Matrix rotate_x_tf = RotateX(static_cast<float>(PI) / 2);
    Matrix scale_tf = Scale(5, 5, 5);
    Matrix translate_tf = Translate(10, 5, 7);

    Point actual1 = rotate_x_tf * p;
    Point expected1{1, -1, 0};

    Point actual2 = scale_tf * actual1;
    Point expected2{5, -5, 0};

    Point actual3 = translate_tf * actual2;
    Point expected3{15, 0, 7};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2) &&
           ASSERT_EQUAL(Point, actual3, expected3);
  });

  fw->Run("Tranformation chain", "Matrix", []() -> bool {
    Point p{1, 0, 1};
    Matrix transform = Translate(10, 5, 7) * Scale(5, 5, 5) *
                       RotateX(static_cast<float>(PI) / 2);

    Point actual = transform * p;
    Point expected{15, 0, 7};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Tranformation chain (fluid)", "Matrix", []() -> bool {
    Point p{1, 0, 1};

    Matrix transform = Identity()
                           .RotateX(static_cast<float>(PI) / 2)
                           .Scale(5, 5, 5)
                           .Translate(10, 5, 7);

    Point actual = transform * p;
    Point expected{15, 0, 7};

    return ASSERT_EQUAL(Point, actual, expected);
  });

  fw->Run("Clock", "Matrix", [fw]() -> bool {
    Canvas canvas{600, 600};
    size_t radius = (canvas.width - 100) / 2;
    Point origin{static_cast<float>(canvas.width) / 2.F, 0.F,
                 static_cast<float>(canvas.height) / 2.F};
    Color green{0, 1, 0};

    size_t resolution = 12;

    std::unique_ptr<Point[]> points = std::make_unique<Point[]>(resolution);

    Point start{0, 0, 1};
    float turn =
        static_cast<float>(PI) / (static_cast<float>(resolution) / 2.F);
    for (size_t i = 0; i < resolution; ++i) {
      float radians = i * turn;
      points[i] = RotateY(radians) * start;

      size_t pos_x = static_cast<size_t>(origin.x + points[i].x * radius);
      size_t pos_y = static_cast<size_t>(origin.z + points[i].z * radius);
      canvas.WriteColor(pos_x, pos_y, green);
    }

    Path output_path = Join(fw->root, "/data/clock.ppm");
    bool res = canvas.SaveToPPM(output_path);

    return ASSERT_EQUAL(bool, res, true);
  });
}

static inline void TestRay(TestFramework* fw) {
  fw->Run("Create and query a ray", "Rays", []() -> bool {
    Point origin{1, 2, 3};
    Vector direction{4, 5, 6};

    Ray ray1{origin, direction};
    Ray ray2;
    ray2.origin = origin;
    ray2.direction = direction;

    return ASSERT_EQUAL(Point, ray1.origin, origin) &&
           ASSERT_EQUAL(Vector, ray1.direction, direction) &&
           ASSERT_EQUAL(Ray, ray1, ray2);
  });

  fw->Run("Compute a point from a distance", "Rays", []() -> bool {
    Ray ray{{2, 3, 4}, {1, 0, 0}};

    Point actual1{ray.Position(0)};
    Point expected1{2, 3, 4};

    Point actual2{ray.Position(1)};
    Point expected2{3, 3, 4};

    Point actual3{ray.Position(-1)};
    Point expected3{1, 3, 4};

    Point actual4{ray.Position(2.5)};
    Point expected4{4.5, 3, 4};

    return ASSERT_EQUAL(Point, actual1, expected1) &&
           ASSERT_EQUAL(Point, actual2, expected2) &&
           ASSERT_EQUAL(Point, actual3, expected3) &&
           ASSERT_EQUAL(Point, actual4, expected4);
  });

  fw->Run("Hit a sphere at two points with a ray", "Rays", []() -> bool {
    Ray ray{{0, 0, -5}, {0, 0, 1}};
    Sphere sphere;
    Hits hits{ray.Intersect(sphere)};

    return ASSERT_EQUAL(size_t, hits.count, 2) &&
           ASSERT_EQUAL_FLOAT(hits[0].t, 4.F) &&
           ASSERT_EQUAL_FLOAT(hits[1].t, 6.F);
  });

  fw->Run("Hit a sphere at a tangent with a ray", "Rays", []() -> bool {
    Ray ray{{0, 1, -5}, {0, 0, 1}};
    Sphere sphere;
    Hits hits{ray.Intersect(sphere)};

    return ASSERT_EQUAL(size_t, hits.count, 1) &&
           ASSERT_EQUAL_FLOAT(hits[0].t, 5.F);
  });

  fw->Run("Miss a sphere with a ray", "Rays", []() -> bool {
    Ray ray{{0, 2, -5}, {0, 0, 1}};
    Sphere sphere;
    Hits hits{ray.Intersect(sphere)};

    return ASSERT_EQUAL(size_t, hits.count, 0);
  });

  fw->Run("Hit a sphere with a ray at its center", "Rays", []() -> bool {
    Ray ray{{0, 0, 0}, {0, 0, 1}};
    Sphere sphere;
    Hits hits{ray.Intersect(sphere)};

    return ASSERT_EQUAL(size_t, hits.count, 2) &&
           ASSERT_EQUAL_FLOAT(hits[0].t, -1.F) &&
           ASSERT_EQUAL_FLOAT(hits[1].t, 1.F);
  });

  fw->Run("Hit a sphere with a ray behind it", "Rays", []() -> bool {
    Ray ray{{0, 0, 5}, {0, 0, 1}};
    Sphere sphere;
    Hits hits{ray.Intersect(sphere)};

    return ASSERT_EQUAL(size_t, hits.count, 2) &&
           ASSERT_EQUAL_FLOAT(hits[0].t, -6.F) &&
           ASSERT_EQUAL_FLOAT(hits[1].t, -4.F);
  });

  fw->Run("Initialize hit and hits", "Rays", []() -> bool {
    Sphere sphere;
    Hit hit{{&sphere, SPHERE}, 3.5};

    Hits hits{Hits{1}};
    hits[0] = hit;

    Hits hits_copy{Hits{hits}};

    return ASSERT_EQUAL_FLOAT(hit.t, 3.5F) &&
           ASSERT_EQUAL(Sphere, *reinterpret_cast<Sphere*>(hit.object.data),
                        sphere) &&
           ASSERT_EQUAL(Hits, hits, hits_copy) &&
           ASSERT_EQUAL(size_t, hits.count, 1) &&
           ASSERT_EQUAL_FLOAT(hits[0].t, 3.5F);
  });

  fw->Run("The hit with all positive t intersections", "Rays", []() -> bool {
    Sphere sphere;

    Hits hits{Hits{
        {{&sphere, SPHERE}, 1},
        {{&sphere, SPHERE}, 2},
    }};

    int32_t idx = hits.FirstHitIdx();
    assert(idx >= 0);
    Hit intersection{hits[idx]};

    return ASSERT_EQUAL(size_t, hits.count, 2) &&
           ASSERT_EQUAL_FLOAT(intersection.t, 1);
  });

  fw->Run("The hit with some negative t intersections", "Rays", []() -> bool {
    Sphere sphere;

    Hits hits{Hits{
        {{&sphere, SPHERE}, -1},
        {{&sphere, SPHERE}, 1},
    }};

    int32_t idx = hits.FirstHitIdx();
    assert(idx >= 0);
    Hit intersection{hits[idx]};

    return ASSERT_EQUAL(size_t, hits.count, 2) &&
           ASSERT_EQUAL_FLOAT(intersection.t, 1);
  });

  fw->Run("The hit with all negative t intersections", "Rays", []() -> bool {
    Sphere sphere;

    Hits hits{Hits{
        {{&sphere, SPHERE}, -2},
        {{&sphere, SPHERE}, -1},
    }};

    int32_t idx = hits.FirstHitIdx();

    return ASSERT_EQUAL(size_t, hits.count, 2) &&
           ASSERT_EQUAL(int32_t, idx, -1);
  });

  fw->Run("The hit with various t intersections", "Rays", []() -> bool {
    Sphere sphere;

    Hits hits{Hits{
        {{&sphere, SPHERE}, 5},
        {{&sphere, SPHERE}, 7},
        {{&sphere, SPHERE}, -3},
        {{&sphere, SPHERE}, 2},
    }};

    int32_t idx = hits.FirstHitIdx();
    assert(idx >= 0);
    Hit intersection{hits[idx]};

    return ASSERT_EQUAL(size_t, hits.count, 4) &&
           ASSERT_EQUAL_FLOAT(intersection.t, 2);
  });

  fw->Run("Translate a ray", "Rays", []() -> bool {
    Ray ray{{1, 2, 3}, {0, 1, 0}};
    Matrix transform{Translate(3, 4, 5)};

    Ray actual{ray.Transform(transform)};
    Ray expected{{4, 6, 8}, {0, 1, 0}};

    return ASSERT_EQUAL(Ray, actual, expected);
  });

  fw->Run("Scale a ray", "Rays", []() -> bool {
    Ray ray{{1, 2, 3}, {0, 1, 0}};
    Matrix transform = Scale(2, 3, 4);

    Ray actual{ray.Transform(transform)};
    Ray expected{{2, 6, 12}, {0, 3, 0}};

    return ASSERT_EQUAL(Ray, actual, expected);
  });

  fw->Run("Default sphere transformation", "Rays", []() -> bool {
    Sphere sphere;
    return ASSERT_EQUAL(Matrix, sphere.transform_matrix, Identity());
  });

  fw->Run("Change sphere transformation", "Rays", []() -> bool {
    Sphere sphere;
    Matrix transform{Translate(2, 3, 4)};
    sphere.transform_matrix = transform;

    return ASSERT_EQUAL(Matrix, sphere.transform_matrix, transform);
  });

  fw->Run("Intersect a scaled sphere with a ray", "Rays", []() -> bool {
    Ray ray{{0, 0, -5}, {0, 0, 1}};

    Sphere sphere;
    sphere.transform_matrix = Scale(2, 2, 2);

    Hits hits{ray.Intersect(sphere)};

    return ASSERT_EQUAL(size_t, hits.count, 2) &&
           ASSERT_EQUAL_FLOAT(hits[0].t, 3.F) &&
           ASSERT_EQUAL_FLOAT(hits[1].t, 7.F);
  });

  fw->Run("Intersect a translated sphere with a ray", "Rays", []() -> bool {
    Ray ray{{0, 0, -5}, {0, 0, 1}};

    Sphere sphere;
    sphere.transform_matrix = Translate(5, 0, 0);

    Hits hits{ray.Intersect(sphere)};

    return ASSERT_EQUAL(size_t, hits.count, 0);
  });

  fw->Run("Cast rays at a sphere", "Rays", [fw]() -> bool {
    size_t canvas_size = 100;
    Canvas canvas{canvas_size, canvas_size};

    Point ray_origin{0, 0, -5};
    Sphere shape;
    shape.material.color = {.26F, .96F, .53F};

    float wall_z = 10.F;
    float wall_size = 7.F;

    CastShapeUnshaded(&canvas, ray_origin, shape, wall_z, wall_size);

    canvas.SaveToPPM(Join(fw->root, "/data/casted_sphere.ppm"));

    return ASSERT_EQUAL(bool, true, true);
  });

  fw->Run("Cast rays at an oval 1", "Rays", [fw]() -> bool {
    size_t canvas_size = 100;
    Canvas canvas{canvas_size, canvas_size};

    Point ray_origin{0, 0, -5};
    Sphere shape;
    shape.material.color = {.26F, .96F, .53F};
    shape.transform_matrix = Scale(1, .5F, 1);

    float wall_z = 10.F;
    float wall_size = 7.F;

    CastShapeUnshaded(&canvas, ray_origin, shape, wall_z, wall_size);

    canvas.SaveToPPM(Join(fw->root, "/data/casted_oval1.ppm"));

    return ASSERT_EQUAL(bool, true, true);
  });

  fw->Run("Cast rays at an oval 2", "Rays", [fw]() -> bool {
    size_t canvas_size = 100;
    Canvas canvas{canvas_size, canvas_size};

    Point ray_origin{0, 0, -5};
    Sphere shape;
    shape.material.color = {.26F, .96F, .53F};
    shape.transform_matrix = Scale(.5F, 1, 1);

    float wall_z = 10.F;
    float wall_size = 7.F;

    CastShapeUnshaded(&canvas, ray_origin, shape, wall_z, wall_size);

    canvas.SaveToPPM(Join(fw->root, "/data/casted_oval2.ppm"));

    return ASSERT_EQUAL(bool, true, true);
  });

  fw->Run("Cast rays at a rotated oval", "Rays", [fw]() -> bool {
    size_t canvas_size = 100;
    Canvas canvas = {canvas_size, canvas_size};

    Point ray_origin{0, 0, -5};
    Sphere shape;
    shape.material.color = {.26F, .96F, .53F};
    shape.transform_matrix =
        Scale(.5F, 1, 1).RotateZ(static_cast<float>(PI) / 4.F);

    float wall_z = 10.F;
    float wall_size = 7.F;

    CastShapeUnshaded(&canvas, ray_origin, shape, wall_z, wall_size);

    canvas.SaveToPPM(Join(fw->root, "/data/casted_rotated_oval.ppm"));

    return ASSERT_EQUAL(bool, true, true);
  });

  fw->Run("Cast rays at a skewed oval", "Rays", [fw]() -> bool {
    size_t canvas_size = 100;
    Canvas canvas{canvas_size, canvas_size};

    Point ray_origin{0, 0, -5};
    Sphere shape;
    shape.material.color = {.26F, .96F, .53F};
    shape.transform_matrix = Shear(XY).Scale(.5F, 1, 1);

    float wall_z = 10.F;
    float wall_size = 7.F;

    CastShapeUnshaded(&canvas, ray_origin, shape, wall_z, wall_size);

    canvas.SaveToPPM(Join(fw->root, "/data/casted_skewed_oval.ppm"));

    return ASSERT_EQUAL(bool, true, true);
  });
}

static inline void TestShading(TestFramework* fw) {
  fw->Run("Normal on a sphere at a point on X axis", "Shading", []() -> bool {
    Sphere sphere;
    Vector actual{sphere.NormalAt({1, 0, 0})};
    Vector expected{1, 0, 0};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Normal on a sphere at a point on Y axis", "Shading", []() -> bool {
    Sphere sphere;
    Vector actual{sphere.NormalAt({0, 1, 0})};
    Vector expected{0, 1, 0};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Normal on a sphere at a point on Z axis", "Shading", []() -> bool {
    Sphere sphere;
    Vector actual{sphere.NormalAt({0, 0, 1})};
    Vector expected{0, 0, 1};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Normal on a sphere at a nonaxial point", "Shading", []() -> bool {
    Sphere sphere;
    Vector actual{sphere.NormalAt(
        {std::sqrt(3.F) / 3.F, std::sqrt(3.F) / 3, std::sqrt(3.F) / 3.F})};
    Vector expected{std::sqrt(3.F) / 3, std::sqrt(3.F) / 3.F,
                    std::sqrt(3.F) / 3.F};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Check that normal is normalized", "Shading", []() -> bool {
    Sphere sphere;
    Vector actual{sphere.NormalAt(
        {std::sqrt(3.F) / 3.F, std::sqrt(3.F) / 3.F, std::sqrt(3.F) / 3.F})};
    Vector expected{std::sqrt(3.F) / 3.F, std::sqrt(3.F) / 3.F,
                    std::sqrt(3.F) / 3.F};
    Vector expected_normalized{actual.Normalize()};

    return ASSERT_EQUAL(Vector, actual, expected) &&
           ASSERT_EQUAL(Vector, actual, expected_normalized);
  });

  fw->Run("Compute the normal on translated sphere", "Shading", []() -> bool {
    Sphere sphere;
    sphere.transform_matrix = Translate(0, 1, 0);

    Vector actual{
        sphere.NormalAt({0, 1 + std::sqrt(2.F) / 2.F, -std::sqrt(2.F) / 2.F})};
    Vector expected{0, std::sqrt(2.F) / 2.F, -std::sqrt(2.F) / 2.F};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Compute the normal on transformed sphere", "Shading", []() -> bool {
    Sphere sphere;
    sphere.transform_matrix =
        RotateZ(static_cast<float>(PI) / 5.F).Scale(1, 0.5F, 1);

    Vector actual{
        sphere.NormalAt({0, std::sqrt(2.F) / 2.F, -std::sqrt(2.F) / 2.F})};
    Vector expected{0, 0.97014250014533F, -0.24253562503633F};

    return ASSERT_EQUAL(Vector, actual, expected);
  });

  fw->Run("Reflect a vector approaching at 45o", "Shading", []() -> bool {
    Vector vector{1, -1, 0};
    Vector normal{0, 1, 0};
    Vector reflect{vector.Reflect(normal)};
    Vector expected{1, 1, 0};

    return ASSERT_EQUAL(Vector, reflect, expected);
  });

  fw->Run("Reflect a vector off a slanted surface", "Shading", []() -> bool {
    Vector vector{0, -1, 0};
    Vector normal{std::sqrt(2.F) / 2.F, std::sqrt(2.F) / 2.F, 0};
    Vector reflect{vector.Reflect(normal)};
    Vector expected{1, 0, 0};

    return ASSERT_EQUAL(Vector, reflect, expected);
  });

  fw->Run("Initialize point light", "Shading", []() -> bool {
    PointLight point_light{{1, 1, 1}, {0, 0, 0}};
    Color expected_intensity = {1, 1, 1};
    Point expected_position = {0, 0, 0};

    return ASSERT_EQUAL(Color, point_light.intensity, expected_intensity) &&
           ASSERT_EQUAL(Point, point_light.position, expected_position);
  });

  fw->Run("Initialize material", "Shading", []() -> bool {
    Material material{{1, 1, 1}, .1F, .9F, .9F, 200.F};

    Color expected_color{1, 1, 1};

    return ASSERT_EQUAL(Color, material.color, expected_color) &&
           ASSERT_EQUAL_FLOAT(material.ambient, .1F) &&
           ASSERT_EQUAL_FLOAT(material.diffuse, .9F) &&
           ASSERT_EQUAL_FLOAT(material.specular, .9F) &&
           ASSERT_EQUAL_FLOAT(material.shininess, 200.F);
  });

  fw->Run("Initialize sphere with default material", "Shading", []() -> bool {
    Material material{{1, 1, 1}, .1F, .9F, .9F, 200.F};
    Sphere sphere1{material};
    Sphere sphere2;

    return ASSERT_EQUAL(Material, sphere1.material, sphere2.material);
  });

  fw->Run("Assign a material to a sphere", "Shading", []() -> bool {
    Material material{{1, 0, 1}, 0, 0, 0, 0};
    Sphere sphere1{material};

    return ASSERT_EQUAL(Material, sphere1.material, material);
  });

  fw->Run("Eye between light and surface", "Shading", []() -> bool {
    Material material;
    Point position = {0, 0, 0};

    Vector eye_vector{0, 0, -1};
    Vector normal_vector{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point{0, 0, -10}};

    Color actual =
        Lighting(material, light, position, eye_vector, normal_vector);
    Color expected{1.9F, 1.9F, 1.9F};

    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Eye (offset 45o) between light, surface", "Shading", []() -> bool {
    Material material;
    Point position = {0, 0, 0};

    Vector eye_vector{0, std::sqrt(2.F) / 2, -std::sqrt(2.F) / 2};
    Vector normal_vector{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point{0, 0, -10}};

    Color actual =
        Lighting(material, light, position, eye_vector, normal_vector);
    Color expected{1.F, 1.F, 1.F};

    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Lighting with light offset 45o", "Shading", []() -> bool {
    Material material;
    Point position = {0, 0, 0};

    Vector eye_vector{0, 0, -1};
    Vector normal_vector{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point{0, 10, -10}};

    Color actual =
        Lighting(material, light, position, eye_vector, normal_vector);
    Color expected{(.1F + .9F * std::sqrt(2.F) / 2.F),
                   (.1F + .9F * std::sqrt(2.F) / 2.F),
                   (.1F + .9F * std::sqrt(2.F) / 2.F)};

    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Eye in the path of the reflection vector", "Shading", []() -> bool {
    Material material;
    Point position = {0, 0, 0};

    Vector eye_vector{0, -sqrt(2.F) / 2.F, -sqrt(2.F) / 2.F};
    Vector normal_vector{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point{0, 10, -10}};

    Color actual =
        Lighting(material, light, position, eye_vector, normal_vector);
    Color expected{(1.F + .9F * sqrt(2.F) / 2.F), (1.F + .9F * sqrt(2.F) / 2.F),
                   (1.F + .9F * sqrt(2.F) / 2.F)};

    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Light behind the surface", "Shading", []() -> bool {
    Material material;
    Point position = {0, 0, 0};

    Vector eye_vector{0, 0, -1};
    Vector normal_vector{0, 0, -1};
    PointLight light{Color(1, 1, 1), Point{0, 0, 10}};

    Color actual =
        Lighting(material, light, position, eye_vector, normal_vector);
    Color expected{.1F, .1F, .1F};

    return ASSERT_EQUAL(Color, actual, expected);
  });

  fw->Run("Cast rays at a sphere (shaded)", "Shading", [fw]() -> bool {
    size_t canvas_size = 100;
    Canvas canvas{canvas_size, canvas_size};

    Point ray_origin{0, 0, -5};
    Sphere shape;
    shape.material.color = {1, .2F, 1};

    PointLight light{Color{1, 1, 1}, Point{-10, 10, -10}};

    float wall_z = 10.F;
    float wall_size = 7.F;

    CastShapeShaded(&canvas, ray_origin, shape, light, wall_z, wall_size);

    canvas.SaveToPPM(Join(fw->root, "/data/casted_shaded_sphere.ppm"));

    return ASSERT_EQUAL(bool, true, true);
  });
}

void RunTests(const char* root) {
  TestFramework fw = TestFramework{root};

  TestArray(&fw);
  TestTuple(&fw);
  TestColor(&fw);
  TestCanvas(&fw);
  TestMatrix(&fw);
  TestRay(&fw);
  TestShading(&fw);

  fw.Summary();
}
