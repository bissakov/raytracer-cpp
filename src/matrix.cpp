#include <src/matrix.h>
#include <src/test_suite.h>

#include <cassert>
#include <cmath>

Matrix::Matrix() noexcept : rows(0), cols(0) {}

Matrix::Matrix(const size_t rows, const size_t cols) noexcept
    : rows(rows), cols(cols) {
  for (size_t i = 0; i < MAX_MATRIX_SIZE; ++i) {
    values[i] = 0.0;
  }
}

Matrix::Matrix(const Matrix& other) noexcept
    : rows(other.rows), cols(other.cols) {
  for (size_t i = 0; i < rows * cols; ++i) {
    values[i] = other.values[i];
  }
}

Matrix& Matrix::operator=(const Matrix& other) noexcept {
  if (this != &other) {
    rows = other.rows;
    cols = other.cols;
    for (size_t i = 0; i < rows * cols; ++i) {
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
  Vector v = {0.0f, 0.0f, 0.0f};

  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      v[i] += At(i, j) * vector[j];
    }
  }

  return v;
}

Point Matrix::operator*(const Point& point) noexcept {
  assert(rows == 4 && cols == 4);
  Point p = {0, 0, 0};
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      p[i] += At(i, j) * point[j];
    }
  }
  return p;
}

Matrix Matrix::operator/(const double scalar) noexcept {
  Matrix res = {rows, cols};
  for (size_t i = 0; i < rows * cols; ++i) {
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

void Matrix::Populate(double* elements, size_t element_count) noexcept {
  assert(element_count == rows * cols &&
         "Invalid number of elements to populate matrix");
  for (size_t i = 0; i < rows * cols; ++i) {
    values[i] = elements[i];
  }
}

Matrix Matrix::Transpose() noexcept {
  Matrix matrix = {rows, cols};

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      matrix.Set(row, col, At(col, row));
    }
  }

  return matrix;
}

double Matrix::Determinant() noexcept {
  if (rows == 2 && cols == 2) {
    return At(0, 0) * At(1, 1) - At(0, 1) * At(1, 0);
  }

  double determinant = 0.0;
  for (size_t col = 0; col < cols; ++col) {
    determinant += At(0, col) * Cofactor(0, col);
  }
  return determinant;
}

Matrix Matrix::SubMatrix(size_t excluded_row, size_t excluded_col) noexcept {
  assert(excluded_row <= rows && excluded_col <= cols);

  Matrix submatrix = {rows - 1, cols - 1};
  size_t current_row = 0;
  size_t current_col = 0;

  for (size_t row = 0; row < rows; ++row) {
    if (row == excluded_row) continue;
    for (size_t col = 0; col < cols; ++col) {
      if (col == excluded_col) continue;

      submatrix.Set(current_row, current_col, At(row, col));
      current_col = (current_col + 1) % submatrix.cols;
    }
    current_row = (current_row + 1) % submatrix.rows;
  }

  return submatrix;
}

double Matrix::Minor(size_t row, size_t col) noexcept {
  Matrix submatrix = SubMatrix(row, col);
  double determinant = submatrix.Determinant();
  return determinant;
}

double Matrix::Cofactor(size_t row, size_t col) noexcept {
  double minor = Minor(row, col);
  double cofactor = ((row + col) % 2 == 0) ? minor : -minor;
  return cofactor;
}

Matrix Matrix::Inverse() noexcept {
  double determinant = Determinant();

  assert(!IsEqualDouble(determinant, 0.0));

  Matrix inversed_matrix = {rows, cols};

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      inversed_matrix.Set(col, row, Cofactor(row, col) / determinant);
    }
  }

  return inversed_matrix;
}

Matrix::operator const char*() const noexcept {
  static char buffer[BUFFER_SIZE];
  size_t buffer_pos = snprintf(
      buffer, sizeof(buffer), "Matrix{\n  rows=%zu, cols=%zu,\n  ", rows, cols);

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      int written = snprintf(buffer + buffer_pos, BUFFER_SIZE - buffer_pos,
                             "%.2f ", At(row, col));
      buffer_pos += written;
    }
    buffer[buffer_pos++] = '\n';
    if (row < rows - 1) {
      buffer[buffer_pos++] = ' ';
      buffer[buffer_pos++] = ' ';
    }
  }
  buffer[buffer_pos++] = '}';
  buffer[buffer_pos] = '\0';

  return buffer;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  os << (const char*)m;
  return os;
}

bool IsEqual(const Matrix& a, const Matrix& b) noexcept {
  if (a.rows != b.rows || a.cols != b.cols) {
    return false;
  }

  for (size_t i = 0; i < a.rows * a.cols; ++i) {
    if (!IsEqualDouble(a.values[i], b.values[i])) {
      return false;
    }
  }

  return true;
}

Matrix Multiply(const Matrix& a, const Matrix& b) noexcept {
  Matrix res = {a.rows, b.cols};

  for (size_t row = 0; row < res.rows; ++row) {
    for (size_t col = 0; col < res.cols; ++col) {
      for (size_t k = 0; k < b.rows; ++k) {
        double product = res.At(row, col) + a.At(row, k) * b.At(k, col);
        res.Set(row, col, product);
      }
    }
  }

  return res;
}

Matrix Matrix::Translate(int32_t x, int32_t y, int32_t z) {
  return ::Translate(x, y, z) * (*this);
}

Matrix Matrix::Scale(int32_t x, int32_t y, int32_t z) {
  return ::Scale(x, y, z) * (*this);
}

Matrix Matrix::RotateX(double radians) {
  return ::RotateX(radians) * (*this);
}

Matrix Matrix::RotateY(double radians) {
  return ::RotateY(radians) * (*this);
}

Matrix Matrix::RotateZ(double radians) {
  return ::RotateZ(radians) * (*this);
}

Matrix Matrix::Shear(ShearType shear_type) {
  return ::Shear(shear_type) * (*this);
}

Matrix Identity() {
  Matrix identity_matrix = {4, 4};
  double elements[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
  identity_matrix.Populate(elements,
                           identity_matrix.rows * identity_matrix.cols);
  return identity_matrix;
}

Matrix Translate(int32_t x, int32_t y, int32_t z) {
  Matrix matrix = Identity();
  matrix.Set(0, 3, x);
  matrix.Set(1, 3, y);
  matrix.Set(2, 3, z);
  return matrix;
}

Matrix Scale(int32_t x, int32_t y, int32_t z) {
  Matrix matrix = Identity();
  matrix.Set(0, 0, x);
  matrix.Set(1, 1, y);
  matrix.Set(2, 2, z);
  return matrix;
}

Matrix RotateX(double radians) {
  Matrix matrix = Identity();
  matrix.Set(1, 1, std::cos(radians));
  matrix.Set(1, 2, -std::sin(radians));
  matrix.Set(2, 1, std::sin(radians));
  matrix.Set(2, 2, std::cos(radians));
  return matrix;
}

Matrix RotateY(double radians) {
  Matrix matrix = Identity();
  matrix.Set(0, 0, std::cos(radians));
  matrix.Set(0, 2, std::sin(radians));
  matrix.Set(2, 0, -std::sin(radians));
  matrix.Set(2, 2, std::cos(radians));
  return matrix;
}

Matrix RotateZ(double radians) {
  Matrix matrix = Identity();
  matrix.Set(0, 0, std::cos(radians));
  matrix.Set(0, 1, -std::sin(radians));
  matrix.Set(1, 0, std::sin(radians));
  matrix.Set(1, 1, std::cos(radians));
  return matrix;
}

Matrix Shear(ShearType shear_type) {
  Matrix matrix = Identity();

  switch (shear_type) {
    case XY: {
      matrix.Set(0, 1, 1.0);
      break;
    }
    case XZ: {
      matrix.Set(0, 2, 1.0);
      break;
    }
    case YX: {
      matrix.Set(1, 0, 1.0);
      break;
    }
    case YZ: {
      matrix.Set(1, 2, 1.0);
      break;
    }
    case ZX: {
      matrix.Set(2, 0, 1.0);
      break;
    }
    case ZY: {
      matrix.Set(2, 1, 1.0);
      break;
    }
  }

  return matrix;
}
