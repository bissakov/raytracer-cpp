#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <immintrin.h>
#include <src/point.h>
#include <src/vector.h>

#include <cassert>
#include <string>

#define BUFFER_SIZE 300

enum ShearType { XY, XZ, YX, YZ, ZX, ZY };

struct Matrix {
  size_t rows;
  size_t cols;

  union {
    __m128 row0;
    struct {
      float m0, m1, m2, m3;
    };
  };

  union {
    __m128 row1;
    struct {
      float m4, m5, m6, m7;
    };
  };

  union {
    __m128 row2;
    struct {
      float m8, m9, m10, m11;
    };
  };

  union {
    __m128 row3;
    struct {
      float m12, m13, m14, m15;
    };
  };

  Matrix() noexcept;
  Matrix(const size_t rows, const size_t cols) noexcept;
  Matrix(const __m128 row0, const __m128 row1, const __m128 row2,
         const __m128 row3) noexcept;
  Matrix(const Matrix& other) noexcept;
  Matrix& operator=(const Matrix& other) noexcept;

  constexpr float& operator[](const size_t index) noexcept;
  constexpr const float& operator[](const size_t index) const noexcept;
  constexpr __m128& Row(const size_t row_idx) noexcept;
  constexpr void SetRow(const __m128 row, const size_t row_idx) noexcept;

  Matrix operator*(const Matrix& other) noexcept;
  Vector operator*(const Vector& vector) noexcept;

  Point operator*(const Point& point) noexcept;

  Matrix operator/(const float scalar) noexcept;
  bool operator==(const Matrix& other) const noexcept;
  bool operator!=(const Matrix& other) const noexcept;

  void Populate(float* elements, size_t element_count) noexcept;
  constexpr bool IsValueInRange(const size_t row,
                                const size_t col) const noexcept;
  Matrix Transpose() noexcept;
  float Determinant() noexcept;
  Matrix SubMatrix(size_t excluded_row, size_t excluded_col) noexcept;
  float Minor(size_t row, size_t col) noexcept;
  float Cofactor(size_t row, size_t col) noexcept;
  Matrix Inverse() noexcept;

  Matrix Translate(float x, float y, float z) noexcept;
  Matrix Scale(float x, float y, float z) noexcept;
  Matrix RotateX(float radians) noexcept;
  Matrix RotateY(float radians) noexcept;
  Matrix RotateZ(float radians) noexcept;
  Matrix Shear(ShearType shear_type) noexcept;

  constexpr size_t Index(const size_t row, const size_t col) const noexcept;
  constexpr float At(const size_t row, const size_t col) const noexcept;
  constexpr void Set(const size_t row, const size_t col,
                     const float value) noexcept;

  operator std::string() const noexcept;
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);

bool IsEqual(const Matrix& a, const Matrix& b) noexcept;
Matrix Multiply(const Matrix& a, const Matrix& b) noexcept;

Matrix Translate(float x, float y, float z) noexcept;
Matrix Scale(float x, float y, float z) noexcept;
Matrix RotateX(float radians) noexcept;
Matrix RotateY(float radians) noexcept;
Matrix RotateZ(float radians) noexcept;
Matrix Shear(ShearType shear_type) noexcept;
Matrix Identity() noexcept;
Matrix Translate(float x, float y, float z) noexcept;

constexpr size_t Matrix::Index(const size_t row,
                               const size_t col) const noexcept {
  return row * 4 + col;
}

constexpr bool Matrix::IsValueInRange(const size_t row,
                                      const size_t col) const noexcept {
  return (row < rows) && (col < cols);
}

constexpr float Matrix::At(const size_t row, const size_t col) const noexcept {
  assert(IsValueInRange(row, col));
  return (*this)[Index(row, col)];
}

constexpr void Matrix::Set(const size_t row, const size_t col,
                           const float value) noexcept {
  (*this)[Index(row, col)] = value;
}

constexpr float& Matrix::operator[](const size_t index) noexcept {
  switch (index) {
    case 0:
      return m0;
    case 1:
      return m1;
    case 2:
      return m2;
    case 3:
      return m3;
    case 4:
      return m4;
    case 5:
      return m5;
    case 6:
      return m6;
    case 7:
      return m7;
    case 8:
      return m8;
    case 9:
      return m9;
    case 10:
      return m10;
    case 11:
      return m11;
    case 12:
      return m12;
    case 13:
      return m13;
    case 14:
      return m14;
  }
  return m15;
}

constexpr const float& Matrix::operator[](const size_t index) const noexcept {
  switch (index) {
    case 0:
      return m0;
    case 1:
      return m1;
    case 2:
      return m2;
    case 3:
      return m3;
    case 4:
      return m4;
    case 5:
      return m5;
    case 6:
      return m6;
    case 7:
      return m7;
    case 8:
      return m8;
    case 9:
      return m9;
    case 10:
      return m10;
    case 11:
      return m11;
    case 12:
      return m12;
    case 13:
      return m13;
    case 14:
      return m14;
  }
  return m15;
}

constexpr __m128& Matrix::Row(const size_t row_idx) noexcept {
  assert(row_idx < rows);
  switch (row_idx) {
    case (0):
      return row0;
    case (1):
      return row1;
    case (2):
      return row2;
  }
  return row3;
}

constexpr void Matrix::SetRow(const __m128 row, const size_t row_idx) noexcept {
  assert(row_idx < rows);
  switch (row_idx) {
    case (0): {
      row0 = row;
      break;
    }
    case (1): {
      row1 = row;
      break;
    }
    case (2): {
      row2 = row;
      break;
    }
  }
  row3 = row;
}

#define INDEX(row, col, matrix) ((row * (matrix).cols) + col)
#define AT(row, col, matrix) ((matrix).values[INDEX(row, col, (matrix))])

#endif  // SRC_MATRIX_H_
