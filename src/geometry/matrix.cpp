#include <core/test_suite.h>
#include <geometry/matrix.h>
#include <immintrin.h>
#include <xmmintrin.h>

#include <cassert>
#include <cmath>
#include <format>
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

Matrix Matrix::operator*(const Matrix& other) const noexcept {
  return Multiply(*this, other);
}

static inline __m128 TupleMultiply(const __m128& row0, const __m128& row1,
                                   const __m128& row2, const __m128& row3,
                                   const __m128& vec) noexcept {
  __m128 res0 = _mm_dp_ps(row0, vec, 0xF1);
  __m128 res1 = _mm_dp_ps(row1, vec, 0xF2);
  __m128 res2 = _mm_dp_ps(row2, vec, 0xF4);
  __m128 res3 = _mm_dp_ps(row3, vec, 0xF8);
  __m128 result = _mm_add_ps(_mm_add_ps(res0, res1), _mm_add_ps(res2, res3));
  return result;
}

Vector Matrix::operator*(const Vector& vector) const noexcept {
  assert(rows == 4 && cols == 4);
  __m128 result = TupleMultiply(row0, row1, row2, row3, vector.vec);
  return Vector{result};
}

Point Matrix::operator*(const Point& point) const noexcept {
  assert(rows == 4 && cols == 4);
  __m128 result = TupleMultiply(row0, row1, row2, row3, point.vec);
  Point p{result};

  return p;
}

Matrix Matrix::operator/(const float scalar) noexcept {
  Matrix res = {rows, cols};
  for (size_t row = 0; row < res.rows; ++row) {
    res.SetRow(_mm_div_ps(Row(row), _mm_set1_ps(scalar)), row);
  }
  return res;
}

bool Matrix::operator==(const Matrix& other) const noexcept {
  if (rows != other.rows || cols != other.cols) {
    return false;
  }

  __m128 tolerance = _mm_set1_ps(static_cast<float>(ABSOLUTE_TOLERANCE));
  __m128 sign_mask = _mm_set1_ps(-0.0F);

  __m128 diff0 = _mm_sub_ps(row0, other.row0);
  __m128 cmp0 = _mm_cmple_ps(_mm_andnot_ps(sign_mask, diff0), tolerance);
  if (_mm_movemask_ps(cmp0) != 0xF) {
    return false;
  }

  __m128 diff1 = _mm_sub_ps(row1, other.row1);
  __m128 cmp1 = _mm_cmple_ps(_mm_andnot_ps(sign_mask, diff1), tolerance);
  if (_mm_movemask_ps(cmp1) != 0xF) {
    return false;
  }

  __m128 diff2 = _mm_sub_ps(row2, other.row2);
  __m128 cmp2 = _mm_cmple_ps(_mm_andnot_ps(sign_mask, diff2), tolerance);
  if (_mm_movemask_ps(cmp2) != 0xF) {
    return false;
  }

  __m128 diff3 = _mm_sub_ps(row3, other.row3);
  __m128 cmp3 = _mm_cmple_ps(_mm_andnot_ps(sign_mask, diff3), tolerance);

  return _mm_movemask_ps(cmp3) == 0xF;
}

bool Matrix::operator!=(const Matrix& other) const noexcept {
  return !(*this == other);
}

void Matrix::Populate(float* elements, const size_t element_count) noexcept {
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

float Matrix::Determinant() const noexcept {
  if (rows == 2 && cols == 2) {
    return At(0, 0) * At(1, 1) - At(0, 1) * At(1, 0);
  }

  float determinant = 0.0;
  for (size_t col = 0; col < cols; ++col) {
    determinant += At(0, col) * Cofactor(0, col);
  }
  return determinant;
}

Matrix Matrix::SubMatrix(size_t excluded_row,
                         size_t excluded_col) const noexcept {
  assert(excluded_row <= rows && excluded_col <= cols);

  Matrix submatrix = {rows - 1, cols - 1};

  size_t current_row = 0;
  size_t current_col = 0;

  for (size_t row = 0; row < rows; ++row) {
    if (row == excluded_row) {
      continue;
    }
    for (size_t col = 0; col < cols; ++col) {
      if (col == excluded_col) {
        continue;
      }

      submatrix.Set(current_row, current_col, At(row, col));
      current_col = (current_col + 1) % submatrix.cols;
    }
    current_row = (current_row + 1) % submatrix.rows;
  }

  return submatrix;
}

float Matrix::Minor(size_t row, size_t col) const noexcept {
  Matrix submatrix = SubMatrix(row, col);
  float determinant = submatrix.Determinant();
  return determinant;
}

float Matrix::Cofactor(size_t row, size_t col) const noexcept {
  float minor = Minor(row, col);
  float cofactor = ((row + col) % 2 == 0) ? minor : -minor;
  return cofactor;
}

Matrix Matrix::Inverse() const noexcept {
  float determinant = Determinant();

  assert(!IsEqualFloat(determinant, 0.0));

  Matrix inversed_matrix = {rows, cols};

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      inversed_matrix[col * 4 + row] = Cofactor(row, col) / determinant;
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

Matrix Matrix::Translate(float x, float y, float z) const noexcept {
  return ::Translate(x, y, z) * (*this);
}

Matrix Matrix::Scale(float x, float y, float z) const noexcept {
  return ::Scale(x, y, z) * (*this);
}

Matrix Matrix::RotateX(float radians) const noexcept {
  return ::RotateX(radians) * (*this);
}

Matrix Matrix::RotateY(float radians) const noexcept {
  return ::RotateY(radians) * (*this);
}

Matrix Matrix::RotateZ(float radians) const noexcept {
  return ::RotateZ(radians) * (*this);
}

Matrix Matrix::Shear(ShearType shear_type) const noexcept {
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
      matrix.m1 = 1.F;
      break;
    }
    case XZ: {
      matrix.m2 = 1.F;
      break;
    }
    case YX: {
      matrix.m4 = 1.F;
      break;
    }
    case YZ: {
      matrix.m6 = 1.F;
      break;
    }
    case ZX: {
      matrix.m8 = 1.F;
      break;
    }
    case ZY: {
      matrix.m9 = 1.F;
      break;
    }
  }

  return matrix;
}

Matrix::operator std::string() const noexcept {
  std::string str = std::format("Matrix(\n  rows={}, cols={},\n  ", rows, cols);

  for (size_t row = 0; row < rows; ++row) {
    for (size_t col = 0; col < cols; ++col) {
      str += std::format("{:.10f}", At(row, col));
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
