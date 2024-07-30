#include <src/matrix.h>
#include <src/test_suite.h>

#include <cassert>
#include <string>

Matrix::Matrix(const int rows_, const int cols_) {
  assert(rows_ >= 0 && cols_ >= 0 && "Dimensions must be positive or 0.");

  rows = rows_;
  cols = rows_;

  values = new float[rows * cols];

  for (int i = 0; i < rows * cols; ++i) {
    values[i] = 0.0f;
  }
}

Matrix::Matrix(const Matrix& other) {
  rows = other.rows;
  cols = other.cols;
  values = new float[rows * cols];
  for (int i = 0; i < rows * cols; ++i) {
    values[i] = other.values[i];
  }
}

Matrix::~Matrix() {
  delete[] values;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    delete[] values;  // Clean up existing values

    values = new float[other.rows * other.cols];
    for (int i = 0; i < other.rows * other.cols; ++i) {
      values[i] = other.values[i];
    }
  }
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) {
  return Multiply(*this, other);
}

bool Matrix::operator==(const Matrix& other) {
  return IsEqual(*this, other);
}

bool Matrix::operator!=(const Matrix& other) {
  return !IsEqual(*this, other);
}

void Matrix::Populate(float* elements, int element_count) {
  assert(element_count == rows * cols &&
         "Invalid number of elements to populate matrix");
  for (int i = 0; i < rows * cols; ++i) {
    values[i] = elements[i];
  }
}

bool Matrix::IsValueInRange(const int row, const int col) const {
  return (row >= 0 && row < rows) && (col >= 0 && col < cols);
}

float Matrix::At(const int row, const int col) const {
  assert(IsValueInRange(row, col));
  return values[row * cols + col];
}

std::string Matrix::ToString() const {
  std::string matrix_str = "Matrix{\n  rows=" + std::to_string(rows) +
                           ", cols=" + std::to_string(cols) + ",\n  ";
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      matrix_str += std::to_string(values[row * cols + col]);

      if (col != cols - 1) {
        matrix_str += ", ";
      }
    }
    if (row != rows - 1) {
      matrix_str += "\n  ";
    }
  }

  matrix_str += "\n}";

  return matrix_str;
}

bool IsEqual(const Matrix& a, const Matrix& b) {
  if (a.rows != b.rows || a.cols != b.cols) {
    return false;
  }

  for (int i = 0; i < a.rows * a.cols; ++i) {
    if (!IsEqualFloat(a.values[i], b.values[i])) {
      return false;
    }
  }

  return true;
}

Matrix Multiply(const Matrix& a, const Matrix& b) {
  assert(a.rows == b.rows && a.cols == b.cols);

  Matrix res = {a.rows, b.cols};

  for (int row = 0; row < res.rows; ++row) {
    for (int col = 0; col < res.cols; ++col) {
      for (int k = 0; k < b.rows; ++k) {
        res.values[row * res.cols + col] += a.At(row, k) * b.At(k, col);
      }
    }
  }

  return res;
}