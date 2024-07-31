#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <src/point_vector.h>

#include <cassert>
#include <string>

struct Matrix {
  int rows;
  int cols;
  float* values;

  Matrix() noexcept;
  Matrix(const int rows_, const int cols_) noexcept;
  Matrix(const Matrix& other) noexcept;
  ~Matrix() noexcept;

  Matrix& operator=(const Matrix& other) noexcept;
  Matrix operator*(const Matrix& other) noexcept;
  Vector operator*(const Vector& vector) noexcept;
  bool operator==(const Matrix& other) const noexcept;
  bool operator!=(const Matrix& other) const noexcept;

  void Populate(float* elements, int element_count) noexcept;
  bool IsValueInRange(const int row, const int col) const noexcept;
  Matrix Transpose() noexcept;
  float Determinant() noexcept;
  Matrix SubMatrix(int excluded_row, int excluded_col) noexcept;

  constexpr int Index(const int row, const int col) const noexcept;
  float At(const int row, const int col) const noexcept;

  std::string ToString() const noexcept;
};

bool IsEqual(const Matrix& a, const Matrix& b) noexcept;
Matrix Multiply(const Matrix& a, const Matrix& b) noexcept;

constexpr int Matrix::Index(const int row, const int col) const noexcept {
  return row * cols + col;
}

Matrix IdentityMatrix();

#define INDEX(row, col, matrix) ((row * (matrix).cols) + col)
#define AT(row, col, matrix) ((matrix).values[INDEX(row, col, (matrix))])

#endif  // SRC_MATRIX_H_
