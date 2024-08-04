#ifndef SRC_ARR_H_
#define SRC_ARR_H_

#include <algorithm>
#include <cassert>
#include <functional>

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

  DyArray(T* array, size_t length_) noexcept
      : length(length_), elements(new T[length]) {
    std::copy(array, array + length, elements);
  }

  DyArray(DyArray&& other) noexcept
      : length(other.length), elements(other.elements) {
    other.length = 0;
    other.elements = nullptr;
  }

  bool operator==(const DyArray<T>& other) noexcept {
    if (length != other.length) {
      return false;
    }

    for (size_t i = 0; i < length; ++i) {
      if (elements[i] != other.elements[i]) {
        return false;
      }
    }

    return true;
  }

  bool operator!=(const DyArray<T>& other) noexcept {
    return !(*this == other);
  }

  bool Compare(T* other_elements, size_t other_length) noexcept {
    if (length != other_length) {
      return false;
    }

    for (size_t i = 0; i < length; ++i) {
      if (elements[i] != other_elements[i]) {
        return false;
      }
    }

    return true;
  }

  DyArray<T>& operator=(const DyArray<T>& other) noexcept {
    if (*this != other) {
      delete[] elements;
      length = other.length;
      elements = new T[other.length];
      std::copy(other.elements, other.elements + other.length, elements);
    }
    return *this;
  }

  DyArray<T>& operator=(DyArray&& other) noexcept {
    if (*this != other) {
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

  void Push(std::function<bool()> test_function, const char* tag,
            const char* name) noexcept {
    T* new_elements = new T[length + 1];
    if (elements != nullptr) {
      std::copy(elements, elements + length, new_elements);
      delete[] elements;
    }
    elements = new_elements;
    elements[length] = {test_function, tag, name};
    length++;
  }

  void Pop() noexcept {
    assert(length > 0);

    if (length == 1) {
      delete[] elements;
      elements = nullptr;
      length = 0;
      return;
    }

    T* new_elements = new T[length - 1];
    std::copy(elements, elements + length - 1, new_elements);
    delete[] elements;
    elements = new_elements;
    length--;
  }

  void Insert(size_t idx, T value) noexcept {
    assert(idx <= length);

    T* new_elements = new T[length + 1];
    if (elements != nullptr) {
      std::copy(elements, elements + idx, new_elements);
      new_elements[idx] = value;
      std::copy(elements + idx, elements + length, new_elements + idx + 1);
      delete[] elements;
    }
    elements = new_elements;
    length++;
  }
};

#endif  // SRC_ARR_H_
