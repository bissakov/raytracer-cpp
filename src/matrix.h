#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <cassert>

struct Matrix {
  int rows;
  int cols;
  float **values;

  Matrix(const int rows_, const int cols_);
  ~Matrix();

  template <typename... T>
  void Populate(T... floats) const {
    float values_[] = {floats...};
    assert(sizeof(values_) == rows * cols * sizeof(float) &&
           "Invalid number of values");
    int idx = 0;
    for (int row = 0; row < rows; ++row) {
      for (int col = 0; col < cols; ++col) {
        values[row][col] = values_[idx++];
      }
    }
  }
  float At(const int row, const int col) const;
  bool IsValueInRange(const int row, const int col) const;
};

#endif  // SRC_MATRIX_H_
