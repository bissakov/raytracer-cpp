#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <src/point.h>
#include <src/vector.h>

#include <cassert>

#define MAX_MATRIX_SIZE 16
#define BUFFER_SIZE 300

enum ShearType { XY, XZ, YX, YZ, ZX, ZY };

struct Matrix {
  size_t rows;
  size_t cols;
  double values[MAX_MATRIX_SIZE];

  Matrix() noexcept;
  Matrix(const size_t rows, const size_t cols) noexcept;
  Matrix(const Matrix& other) noexcept;
  Matrix& operator=(const Matrix& other) noexcept;

  Matrix operator*(const Matrix& other) noexcept;
  Vector operator*(const Vector& vector) noexcept;

  Point operator*(const Point& point) noexcept;

  Matrix operator/(const double scalar) noexcept;
  bool operator==(const Matrix& other) const noexcept;
  bool operator!=(const Matrix& other) const noexcept;

  void Populate(double* elements, size_t element_count) noexcept;
  constexpr bool IsValueInRange(const size_t row,
                                const size_t col) const noexcept;
  Matrix Transpose() noexcept;
  double Determinant() noexcept;
  Matrix SubMatrix(size_t excluded_row, size_t excluded_col) noexcept;
  double Minor(size_t row, size_t col) noexcept;
  double Cofactor(size_t row, size_t col) noexcept;
  Matrix Inverse() noexcept;

  Matrix Translate(int32_t x, int32_t y, int32_t z);
  Matrix Scale(int32_t x, int32_t y, int32_t z);
  Matrix RotateX(double radians);
  Matrix RotateY(double radians);
  Matrix RotateZ(double radians);
  Matrix Shear(ShearType shear_type);

  constexpr size_t Index(const size_t row, const size_t col) const noexcept;
  constexpr double At(const size_t row, const size_t col) const noexcept;
  constexpr void Set(const size_t row, const size_t col,
                     const double value) noexcept;

  operator const char*() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);

bool IsEqual(const Matrix& a, const Matrix& b) noexcept;
Matrix Multiply(const Matrix& a, const Matrix& b) noexcept;

Matrix Translate(int32_t x, int32_t y, int32_t z);
Matrix Scale(int32_t x, int32_t y, int32_t z);
Matrix RotateX(double radians);
Matrix RotateY(double radians);
Matrix RotateZ(double radians);
Matrix Shear(ShearType shear_type);

constexpr size_t Matrix::Index(const size_t row,
                               const size_t col) const noexcept {
  return row * cols + col;
}

constexpr bool Matrix::IsValueInRange(const size_t row,
                                      const size_t col) const noexcept {
  return (row < rows) && (col < cols);
}

constexpr double Matrix::At(const size_t row, const size_t col) const noexcept {
  assert(IsValueInRange(row, col));
  return values[Index(row, col)];
}

constexpr void Matrix::Set(const size_t row, const size_t col,
                           const double value) noexcept {
  values[Index(row, col)] = value;
}

Matrix Identity();
Matrix Translate(int32_t x, int32_t y, int32_t z);

#define INDEX(row, col, matrix) ((row * (matrix).cols) + col)
#define AT(row, col, matrix) ((matrix).values[INDEX(row, col, (matrix))])

#endif  // SRC_MATRIX_H_
