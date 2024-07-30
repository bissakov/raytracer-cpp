#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cassert>
#include <string>

struct Matrix {
  int rows;
  int cols;
  float* values;

  Matrix(const int rows_, const int cols_);
  Matrix(const Matrix& other);
  ~Matrix();

  Matrix& operator=(const Matrix& other);
  Matrix operator*(const Matrix& other);
  bool operator==(const Matrix& other);
  bool operator!=(const Matrix& other);

  void Populate(float* elements, int element_count);
  bool IsValueInRange(const int row, const int col) const;
  float At(const int row, const int col) const;

  std::string ToString() const;
};

bool IsEqual(const Matrix& a, const Matrix& b);
Matrix Multiply(const Matrix& a, const Matrix& b);

#endif  // SRC_MATRIX_H_
