#include <src/matrix.h>
#include <src/test_suite.h>

#include <cassert>
#include <string>

Matrix::Matrix() noexcept {
  rows = 0;
  cols = 0;
  values = nullptr;
}

Matrix::Matrix(const int rows_, const int cols_) noexcept {
  assert(rows_ >= 0 && cols_ >= 0 && "Dimensions must be positive or 0.");

  rows = rows_;
  cols = rows_;

  values = new double[rows * cols];

  for (int i = 0; i < rows * cols; ++i) {
    values[i] = 0.0f;
  }
}

Matrix::Matrix(const Matrix& other) noexcept {
  rows = other.rows;
  cols = other.cols;
  values = new double[rows * cols];
  for (int i = 0; i < rows * cols; ++i) {
    values[i] = other.values[i];
  }
}

Matrix::~Matrix() noexcept {
  delete[] values;
}

double Matrix::At(const int row, const int col) const noexcept {
  assert(IsValueInRange(row, col));
  return values[Index(row, col)];
}

Matrix& Matrix::operator=(const Matrix& other) noexcept {
  if (this != &other) {
    delete[] values;

    values = new double[other.rows * other.cols];
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

Matrix Matrix::operator/(const double scalar) noexcept {
  Matrix res = {rows, cols};
  for (int i = 0; i < rows * cols; ++i) {
    res.values[i] /= scalar;
  }
  return res;
}

bool Matrix::operator==(const Matrix& other) const noexcept {
  return IsEqual(*this, other);
}

bool Matrix::operator!=(const Matrix& other) const noexcept {
  return !IsEqual(*this, other);
}

void Matrix::Populate(double* elements, int element_count) noexcept {
  assert(element_count == rows * cols &&
         "Invalid number of elements to populate matrix");
  for (int i = 0; i < rows * cols; ++i) {
    values[i] = elements[i];
  }
}

bool Matrix::IsValueInRange(const int row, const int col) const noexcept {
  return (row >= 0 && row < rows) && (col >= 0 && col < cols);
}

Matrix Matrix::Transpose() noexcept {
  Matrix matrix = {rows, cols};

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      matrix.values[matrix.Index(row, col)] = At(col, row);
    }
  }

  return matrix;
}

double Matrix::Determinant() noexcept {
  if (rows == 2 && cols == 2) {
    return At(0, 0) * At(1, 1) - At(0, 1) * At(1, 0);
  }

  double determinant = 0.0;
  for (int col = 0; col < cols; ++col) {
    determinant += At(0, col) * Cofactor(0, col);
  }
  return determinant;
}

Matrix Matrix::SubMatrix(int excluded_row, int excluded_col) noexcept {
  assert(excluded_row >= 0 && excluded_row <= rows && excluded_col >= 0 &&
         excluded_col <= cols);

  Matrix submatrix = {rows - 1, cols - 1};
  int current_row = 0;
  int current_col = 0;

  for (int row = 0; row < rows; ++row) {
    if (row == excluded_row) continue;
    for (int col = 0; col < cols; ++col) {
      if (col == excluded_col) continue;

      int index = submatrix.Index(current_row, current_col);
      submatrix.values[index] = At(row, col);
      current_col = (current_col + 1) % submatrix.cols;
    }
    current_row = (current_row + 1) % submatrix.rows;
  }

  return submatrix;
}

double Matrix::Minor(int row, int col) noexcept {
  Matrix submatrix = SubMatrix(row, col);
  double determinant = submatrix.Determinant();
  return determinant;
}

double Matrix::Cofactor(int row, int col) noexcept {
  double minor = Minor(row, col);
  double cofactor = ((row + col) % 2 == 0) ? minor : -minor;
  return cofactor;
}

Matrix Matrix::Inverse() noexcept {
  double determinant = Determinant();

  assert(!IsEqualDouble(determinant, 0.0));

  Matrix inversed_matrix = {rows, cols};

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      inversed_matrix.values[Index(col, row)] =
          Cofactor(row, col) / determinant;
    }
  }

  return inversed_matrix;
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
    if (!IsEqualDouble(a.values[i], b.values[i])) {
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

Matrix IdentityMatrix() {
  Matrix identity_matrix = {4, 4};
  double elements[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  identity_matrix.Populate(elements,
                           identity_matrix.rows * identity_matrix.cols);
  return identity_matrix;
}
