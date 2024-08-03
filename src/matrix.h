#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <src/point_vector.h>

#include <algorithm>
#include <cassert>
#include <string>

struct Matrix {
  size_t rows;
  size_t cols;
  double* values;

  Matrix() noexcept : rows(0), cols(0), values(nullptr) {}

  Matrix(const size_t rows_, const size_t cols_) noexcept
      : rows(rows_), cols(cols_), values(new double[rows * cols]()) {}

  Matrix(const Matrix& other) noexcept
      : rows(other.rows),
        cols(other.cols),
        values(new double[other.rows * other.cols]) {
    std::copy(other.values, other.values + rows * cols, values);
  }

  ~Matrix() noexcept {
    delete[] values;
  }

  Matrix& operator=(const Matrix& other) noexcept;
  Matrix operator*(const Matrix& other) noexcept;
  Vector operator*(const Vector& vector) noexcept;

  // TODO(bissakov): to complete
  Point operator*(const Point& point) noexcept;

  Matrix operator/(const double scalar) noexcept;
  bool operator==(const Matrix& other) const noexcept;
  bool operator!=(const Matrix& other) const noexcept;

  void Populate(double* elements, size_t element_count) noexcept;
  bool IsValueInRange(const size_t row, const size_t col) const noexcept;
  Matrix Transpose() noexcept;
  double Determinant() noexcept;
  Matrix SubMatrix(size_t excluded_row, size_t excluded_col) noexcept;
  double Minor(size_t row, size_t col) noexcept;
  double Cofactor(size_t row, size_t col) noexcept;
  Matrix Inverse() noexcept;

  constexpr size_t Index(const size_t row, const size_t col) const noexcept;
  double At(const size_t row, const size_t col) const noexcept;

  std::string ToString() const noexcept;
};

bool IsEqual(const Matrix& a, const Matrix& b) noexcept;
Matrix Multiply(const Matrix& a, const Matrix& b) noexcept;

// TODO(bissakov): to complete
Matrix Translate(int32_t x, int32_t y, int32_t z);

constexpr size_t Matrix::Index(const size_t row,
                               const size_t col) const noexcept {
  return row * cols + col;
}

Matrix IdentityMatrix();

#define INDEX(row, col, matrix) ((row * (matrix).cols) + col)
#define AT(row, col, matrix) ((matrix).values[INDEX(row, col, (matrix))])

#endif  // SRC_MATRIX_H_
