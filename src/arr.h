#ifndef SRC_ARR_H_
#define SRC_ARR_H_

#include <algorithm>
#include <cassert>

template <typename T>
struct DyArray {
  size_t length;
  T* elements;

  explicit DyArray(const size_t length_) noexcept
      : length(length_), elements(new T[length]) {}

  DyArray() noexcept : length(0), elements(nullptr) {}

  explicit DyArray(const DyArray& other) noexcept
      : length(other.length), elements(new T[other.length]) {
    std::copy(other.elements, other.elements + other.length, elements);
  }

  DyArray(DyArray&& other) noexcept
      : length(other.length), elements(other.elements) {
    other.length = 0;
    other.elements = nullptr;
  }

  DyArray<T>& operator=(const DyArray<T>& other) noexcept {
    if (this != &other) {
      delete[] elements;
      length = other.length;
      elements = new T[other.length];
      std::copy(other.elements, other.elements + other.length, elements);
    }
    return *this;
  }

  DyArray<T>& operator=(DyArray&& other) noexcept {
    if (this != &other) {
      delete[] elements;
      length = other.length;
      elements = other.elements;
      other.length = 0;
      other.elements = nullptr;
    }
    return *this;
  }

  ~DyArray<T>() noexcept {
    delete[] elements;
  }

  T& Get(size_t index) const {
    assert(index < length);
    return elements[index];
  }

  void Push(T element) noexcept {
    T* new_elements = new T[length + 1];
    if (elements != nullptr) {
      std::copy(elements, elements + length, new_elements);
      delete[] elements;
    }
    elements = new_elements;
    elements[length] = element;
    length++;
  }

  void Pop() noexcept {
    T* new_elements;
    if (length - 1 == 0) {
      new_elements = nullptr;
    } else {
      new_elements = new T[length - 1];
      if (elements != nullptr) {
        std::copy(elements, elements + length - 1, new_elements);
        delete[] elements;
      }
    }
    elements = new_elements;
    length--;
  }

  void Insert(size_t idx, T value) noexcept {
    assert(length >= 0);
    T* new_elements = new T[length + 1];
    if (elements != nullptr) {
      if (idx == 0) {
        std::copy(idx + 1, elements + length, new_elements);
      } else if (idx == length - 1) {
        std::copy(0, elements + length - 1, new_elements);
      }
      std::copy(elements, elements + length, new_elements);
      delete[] elements;
    }
    elements = new_elements;
    elements[length] = value;
    length++;
  }
};

#endif  // SRC_ARR_H_
