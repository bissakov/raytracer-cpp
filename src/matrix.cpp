#include <src/matrix.h>
#include <src/test_suite.h>

#include <cassert>
#include <string>

Matrix::Matrix(const int rows_, const int cols_) noexcept {
  assert(rows_ >= 0 && cols_ >= 0 && "Dimensions must be positive or 0.");

  rows = rows_;
  cols = rows_;

  values = new float[rows * cols];

  for (int i = 0; i < rows * cols; ++i) {
    values[i] = 0.0f;
  }
}

Matrix::Matrix(const Matrix& other) noexcept {
  rows = other.rows;
  cols = other.cols;
  values = new float[rows * cols];
  for (int i = 0; i < rows * cols; ++i) {
    values[i] = other.values[i];
  }
}

Matrix::~Matrix() noexcept {
  delete[] values;
}

inline float Matrix::At(const int row, const int col) const noexcept {
  assert(IsValueInRange(row, col));
  return values[Index(row, col)];
}

Matrix& Matrix::operator=(const Matrix& other) noexcept {
  if (this != &other) {
    delete[] values;

    values = new float[other.rows * other.cols];
    for (int i = 0; i < other.rows * other.cols; ++i) {
      values[i] = other.values[i];
    }
  }
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) noexcept {
  return Multiply(*this, other);
}

Vector Matrix::operator*(const Vector& vector) noexcept {
  assert(rows == 4 && cols == 4);
  Vector res = {0.0f, 0.0f, 0.0f, 0.0f};

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      res[i] += At(i, j) * vector[j];
    }
  }

  return res;
}

bool Matrix::operator==(const Matrix& other) noexcept {
  return IsEqual(*this, other);
}

bool Matrix::operator!=(const Matrix& other) noexcept {
  return !IsEqual(*this, other);
}

void Matrix::Populate(float* elements, int element_count) noexcept {
  assert(element_count == rows * cols &&
         "Invalid number of elements to populate matrix");
  for (int i = 0; i < rows * cols; ++i) {
    values[i] = elements[i];
  }
}

bool Matrix::IsValueInRange(const int row, const int col) const noexcept {
  return (row >= 0 && row < rows) && (col >= 0 && col < cols);
}

std::string Matrix::ToString() const noexcept {
  std::string matrix_str = "Matrix{\n  rows=" + std::to_string(rows) +
                           ", cols=" + std::to_string(cols) + ",\n  ";
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      matrix_str += std::to_string(At(row, col));

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

bool IsEqual(const Matrix& a, const Matrix& b) noexcept {
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

Matrix Multiply(const Matrix& a, const Matrix& b) noexcept {
  Matrix res = {a.rows, b.cols};

  for (int row = 0; row < res.rows; ++row) {
    for (int col = 0; col < res.cols; ++col) {
      for (int k = 0; k < b.rows; ++k) {
        res.values[res.Index(row, col)] += a.At(row, k) * b.At(k, col);
      }
    }
  }

  return res;
}
