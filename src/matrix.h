#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <immintrin.h>
#include <src/point.h>
#include <src/vector.h>

#include <cassert>
#include <string>

#define BUFFER_SIZE 300

enum ShearType { XY, XZ, YX, YZ, ZX, ZY };

struct Matrix {
  size_t rows;
  size_t cols;

  union {
    __m256d row0;
    struct {
      double m0;
      double m1;
      double m2;
      double m3;
    };
  };

  union {
    __m256d row1;
    struct {
      double m4;
      double m5;
      double m6;
      double m7;
    };
  };

  union {
    __m256d row2;
    struct {
      double m8;
      double m9;
      double m10;
      double m11;
    };
  };

  union {
    __m256d row3;
    struct {
      double m12;
      double m13;
      double m14;
      double m15;
    };
  };

  Matrix() noexcept;
  Matrix(const size_t rows, const size_t cols) noexcept;
  Matrix(const Matrix& other) noexcept;
  Matrix& operator=(const Matrix& other) noexcept;

  constexpr double& operator[](const size_t index) noexcept;
  constexpr const double& operator[](const size_t index) const noexcept;

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

  Matrix Translate(double x, double y, double z) noexcept;
  Matrix Scale(double x, double y, double z) noexcept;
  Matrix RotateX(double radians) noexcept;
  Matrix RotateY(double radians) noexcept;
  Matrix RotateZ(double radians) noexcept;
  Matrix Shear(ShearType shear_type) noexcept;

  constexpr size_t Index(const size_t row, const size_t col) const noexcept;
  constexpr double At(const size_t row, const size_t col) const noexcept;
  constexpr void Set(const size_t row, const size_t col,
                     const double value) noexcept;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);

bool IsEqual(const Matrix& a, const Matrix& b) noexcept;
Matrix Multiply(const Matrix& a, const Matrix& b) noexcept;

Matrix Translate(double x, double y, double z) noexcept;
Matrix Scale(double x, double y, double z) noexcept;
Matrix RotateX(double radians) noexcept;
Matrix RotateY(double radians) noexcept;
Matrix RotateZ(double radians) noexcept;
Matrix Shear(ShearType shear_type) noexcept;
Matrix Identity() noexcept;
Matrix Translate(double x, double y, double z) noexcept;

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
  return (*this)[Index(row, col)];
}

constexpr void Matrix::Set(const size_t row, const size_t col,
                           const double value) noexcept {
  (*this)[Index(row, col)] = value;
}

constexpr double& Matrix::operator[](const size_t index) noexcept {
  assert(index < rows * cols);
  switch (index) {
    case 0:
      return m0;
    case 1:
      return m1;
    case 2:
      return m2;
    case 3:
      return m3;
    case 4:
      return m4;
    case 5:
      return m5;
    case 6:
      return m6;
    case 7:
      return m7;
    case 8:
      return m8;
    case 9:
      return m9;
    case 10:
      return m10;
    case 11:
      return m11;
    case 12:
      return m12;
    case 13:
      return m13;
    case 14:
      return m14;
  }
  return m15;
}

constexpr const double& Matrix::operator[](const size_t index) const noexcept {
  assert(index < rows * cols);
  switch (index) {
    case 0:
      return m0;
    case 1:
      return m1;
    case 2:
      return m2;
    case 3:
      return m3;
    case 4:
      return m4;
    case 5:
      return m5;
    case 6:
      return m6;
    case 7:
      return m7;
    case 8:
      return m8;
    case 9:
      return m9;
    case 10:
      return m10;
    case 11:
      return m11;
    case 12:
      return m12;
    case 13:
      return m13;
    case 14:
      return m14;
  }
  return m15;
}

#define INDEX(row, col, matrix) ((row * (matrix).cols) + col)
#define AT(row, col, matrix) ((matrix).values[INDEX(row, col, (matrix))])

#endif  // SRC_MATRIX_H_
