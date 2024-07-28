#include <src/matrix.h>

#include <cassert>

Matrix::Matrix(const int rows_, const int cols_) {
  rows = rows_;
  cols = cols_;

  assert(cols >= 0 && rows >= 0 && "Dimensions must be positive or 0.");

  if (rows_ == 0 && cols_ == 0) {
    values = nullptr;
    return;
  }

  values = new float *[rows];
  for (int row = 0; row < rows; ++row) {
    values[row] = new float[cols];
    for (int col = 0; col < cols; ++col) {
      float *value = &values[row][col];
      *value = 0.0f;
    }
  }
}

Matrix::~Matrix() {
  if ((rows == 0 && cols == 0) || values == nullptr) {
    return;
  }

  for (int row = 0; row < rows; ++row) {
    if (values[row] == nullptr) {
      delete[] values[row];
    }
  }
  delete[] values;
}

bool Matrix::IsValueInRange(const int row, const int col) const {
  return (row >= 0 && row < rows) && (col >= 0 && col < cols);
}

float Matrix::At(const int row, const int col) const {
  assert(IsValueInRange(row, col));
  assert(values != nullptr);

  return values[row][col];
}
