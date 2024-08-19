#include <core/test_suite.h>
#include <geometry/matrix.h>
#include <immintrin.h>

#include <cassert>
#include <cmath>
#include <string>

Matrix::Matrix() noexcept
    : rows(0),
      cols(0),
      row0(_mm_setzero_ps()),
      row1(_mm_setzero_ps()),
      row2(_mm_setzero_ps()),
      row3(_mm_setzero_ps()) {}

Matrix::Matrix(const size_t rows, const size_t cols) noexcept
    : rows(rows),
      cols(cols),
      row0(_mm_setzero_ps()),
      row1(_mm_setzero_ps()),
      row2(_mm_setzero_ps()),
      row3(_mm_setzero_ps()) {}

Matrix::Matrix(const __m128 row0, const __m128 row1, const __m128 row2,
               const __m128 row3) noexcept
    : rows(4), cols(4), row0(row0), row1(row1), row2(row2), row3(row3) {}

Matrix::Matrix(const Matrix& other) noexcept
    : rows(other.rows),
      cols(other.cols),
      row0(other.row0),
      row1(other.row1),
      row2(other.row2),
      row3(other.row3) {}

Matrix& Matrix::operator=(const Matrix& other) noexcept {
  if (this != &other) {
    rows = other.rows;
    cols = other.cols;
    row0 = other.row0;
    row1 = other.row1;
    row2 = other.row2;
    row3 = other.row3;
  }
  return *this;
}

Matrix Matrix::operator*(const Matrix& other) noexcept {
  return Multiply(*this, other);
}

Vector Matrix::operator*(const Vector& vector) noexcept {
  assert(rows == 4 && cols == 4);
  Vector v;

  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      v[i] += At(i, j) * vector[j];
    }
  }

  return v;
}

Point Matrix::operator*(const Point& point) noexcept {
  assert(rows == 4 && cols == 4);
  Point p;
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      p[i] += At(i, j) * point[j];
    }
  }
  return p;
}

Matrix Matrix::operator/(const float scalar) noexcept {
  Matrix res = {rows, cols};
  for (size_t row = 0; row < rows; ++row) {
    res.SetRow(_mm_div_ps(Row(row), _mm_set1_ps(scalar)), row);
  }
  return res;
}

bool Matrix::operator==(const Matrix& other) const noexcept {
  if (rows != other.rows || cols != other.cols) {
    return false;
  }

  for (size_t i = 0; i < rows * cols; ++i) {
    if (!IsEqualFloat((*this)[i], other[i])) {
      return false;
    }
  }

  return true;
}

bool Matrix::operator!=(const Matrix& other) const noexcept {
  return !(*this == other);
}

void Matrix::Populate(float* elements, size_t element_count) noexcept {
  assert(element_count == rows * cols &&
         "Invalid number of elements to populate matrix");
  size_t i = 0;
  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      (*this)[Index(row, col)] = elements[i];
      i++;
    }
  }
}

Matrix Matrix::Transpose() noexcept {
  Matrix matrix(*this);
  _MM_TRANSPOSE4_PS(matrix.row0, matrix.row1, matrix.row2, matrix.row3);
  return matrix;
}

float Matrix::Determinant() noexcept {
  if (rows == 2 && cols == 2) {
    return At(0, 0) * At(1, 1) - At(0, 1) * At(1, 0);
  }

  float determinant = 0.0;
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

float Matrix::Minor(size_t row, size_t col) noexcept {
  Matrix submatrix = SubMatrix(row, col);
  float determinant = submatrix.Determinant();
  return determinant;
}

float Matrix::Cofactor(size_t row, size_t col) noexcept {
  float minor = Minor(row, col);
  float cofactor = ((row + col) % 2 == 0) ? minor : -minor;
  return cofactor;
}

Matrix Matrix::Inverse() noexcept {
  float determinant = Determinant();

  assert(!IsEqualFloat(determinant, 0.0));

  Matrix inversed_matrix = {rows, cols};

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      inversed_matrix.Set(col, row, Cofactor(row, col) / determinant);
    }
  }

  return inversed_matrix;
}

Matrix Multiply(const Matrix& a, const Matrix& b) noexcept {
  __m128 row0 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m0), b.row0),
                                      _mm_mul_ps(_mm_set1_ps(a.m1), b.row1)),
                           _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m2), b.row2),
                                      _mm_mul_ps(_mm_set1_ps(a.m3), b.row3)));

  __m128 row1 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m4), b.row0),
                                      _mm_mul_ps(_mm_set1_ps(a.m5), b.row1)),
                           _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m6), b.row2),
                                      _mm_mul_ps(_mm_set1_ps(a.m7), b.row3)));

  __m128 row2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m8), b.row0),
                                      _mm_mul_ps(_mm_set1_ps(a.m9), b.row1)),
                           _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m10), b.row2),
                                      _mm_mul_ps(_mm_set1_ps(a.m11), b.row3)));

  __m128 row3 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m12), b.row0),
                                      _mm_mul_ps(_mm_set1_ps(a.m13), b.row1)),
                           _mm_add_ps(_mm_mul_ps(_mm_set1_ps(a.m14), b.row2),
                                      _mm_mul_ps(_mm_set1_ps(a.m15), b.row3)));
  Matrix res(row0, row1, row2, row3);
  res.rows = a.rows;
  res.cols = b.cols;

  return res;
}

Matrix Matrix::Translate(float x, float y, float z) noexcept {
  return ::Translate(x, y, z) * (*this);
}

Matrix Matrix::Scale(float x, float y, float z) noexcept {
  return ::Scale(x, y, z) * (*this);
}

Matrix Matrix::RotateX(float radians) noexcept {
  return ::RotateX(radians) * (*this);
}

Matrix Matrix::RotateY(float radians) noexcept {
  return ::RotateY(radians) * (*this);
}

Matrix Matrix::RotateZ(float radians) noexcept {
  return ::RotateZ(radians) * (*this);
}

Matrix Matrix::Shear(ShearType shear_type) noexcept {
  return ::Shear(shear_type) * (*this);
}

Matrix Identity() noexcept {
  Matrix identity_matrix{_mm_set_ps(0, 0, 0, 1), _mm_set_ps(0, 0, 1, 0),
                         _mm_set_ps(0, 1, 0, 0), _mm_set_ps(1, 0, 0, 0)};
  return identity_matrix;
}

Matrix Translate(float x, float y, float z) noexcept {
  Matrix matrix{Identity()};
  matrix.m3 = x;
  matrix.m7 = y;
  matrix.m11 = z;
  return matrix;
}

Matrix Scale(float x, float y, float z) noexcept {
  Matrix matrix{Identity()};
  matrix.m0 = x;
  matrix.m5 = y;
  matrix.m10 = z;
  return matrix;
}

Matrix RotateX(float radians) noexcept {
  Matrix matrix{Identity()};
  matrix.m5 = std::cos(radians);
  matrix.m6 = -std::sin(radians);
  matrix.m9 = std::sin(radians);
  matrix.m10 = std::cos(radians);
  return matrix;
}

Matrix RotateY(float radians) noexcept {
  Matrix matrix{Identity()};
  matrix.m0 = std::cos(radians);
  matrix.m2 = std::sin(radians);
  matrix.m8 = -std::sin(radians);
  matrix.m10 = std::cos(radians);
  return matrix;
}

Matrix RotateZ(float radians) noexcept {
  Matrix matrix{Identity()};
  matrix.m0 = std::cos(radians);
  matrix.m1 = -std::sin(radians);
  matrix.m4 = std::sin(radians);
  matrix.m5 = std::cos(radians);
  return matrix;
}

Matrix Shear(ShearType shear_type) noexcept {
  Matrix matrix{Identity()};

  switch (shear_type) {
    case XY: {
      matrix.m1 = 1.f;
      break;
    }
    case XZ: {
      matrix.m2 = 1.f;
      break;
    }
    case YX: {
      matrix.m4 = 1.f;
      break;
    }
    case YZ: {
      matrix.m6 = 1.f;
      break;
    }
    case ZX: {
      matrix.m8 = 1.f;
      break;
    }
    case ZY: {
      matrix.m9 = 1.f;
      break;
    }
  }

  return matrix;
}

Matrix::operator std::string() const noexcept {
  std::string str = "Matrix{\n  rows=" + std::to_string(rows) +
                    ", cols=" + std::to_string(cols) + ",\n  ";

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      str += std::to_string(At(row, col)) + " ";
    }
    str += "\n";
    if (row < rows - 1) {
      str += "  ";
    }
  }
  str += "}";

  return str;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  os << std::string(m);
  return os;
}
