#ifndef SRC_ARR_H_
#define SRC_ARR_H_

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>

template <typename T>
struct DyArray {
  size_t size;
  size_t capacity;
  std::unique_ptr<T[]> data;

  explicit DyArray(const size_t length) noexcept
      : size(length), capacity(length), data(std::make_unique<T[]>(capacity)) {}

  DyArray() noexcept : size(0), capacity(0), data(nullptr) {}

  explicit DyArray(const DyArray& other) noexcept
      : size(other.size),
        capacity(other.capacity),
        data(std::make_unique<T[]>(other.capacity)) {
    std::copy(other.data.get(), other.data.get() + other.size, data.get());
  }

  DyArray(T* array, size_t length) noexcept
      : size(length), capacity(length), data(std::make_unique<T[]>(capacity)) {
    std::copy(array, array + length, data.get());
  }

  DyArray(std::shared_ptr<T[]> array, size_t length) noexcept
      : size(length), capacity(length), data(std::make_unique<T[]>(length)) {
    std::copy(array.get(), array.get() + length, data.get());
  }

  DyArray(DyArray&& other) noexcept
      : size(other.size),
        capacity(other.capacity),
        data(std::move(other.data)) {
    other.size = 0;
    other.capacity = 0;
  }

  DyArray& operator=(const DyArray& other) noexcept {
    if (this != &other) {
      size = other.size;
      capacity = other.capacity;
      data = std::make_unique<T[]>(other.capacity);
      std::copy(other.data.get(), other.data.get() + other.size, data.get());
    }
    return *this;
  }

  DyArray& operator=(DyArray&& other) noexcept {
    if (this != &other) {
      size = other.size;
      capacity = other.capacity;
      data = std::move(other.data);
      other.size = 0;
      other.capacity = 0;
    }
    return *this;
  }

  T& operator[](size_t index) noexcept {
    assert(index < size);
    return data[index];
  }

  const T& operator[](size_t index) const noexcept {
    assert(index < size);
    return data[index];
  }

  bool operator==(const DyArray<T>& other) noexcept {
    if (size != other.size || capacity != other.capacity) {
      return false;
    }

    for (size_t i = 0; i < size; ++i) {
      if (data[i] != other.data[i]) {
        return false;
      }
    }

    return true;
  }

  bool operator!=(const DyArray<T>& other) noexcept {
    return !(*this == other);
  }

  bool Compare(T* other_data, size_t other_size) noexcept {
    if (size != other_size) {
      return false;
    }

    for (size_t i = 0; i < size; ++i) {
      if (data[i] != other_data[i]) {
        return false;
      }
    }

    return true;
  }

  bool Compare(std::shared_ptr<T[]> other_data, size_t other_size) noexcept {
    if (size != other_size) {
      return false;
    }

    for (size_t i = 0; i < size; ++i) {
      if (data[i] != other_data[i]) {
        return false;
      }
    }

    return true;
  }

  T& Get(size_t index) const {
    assert(index < size);
    return data[index];
  }

  void Push(const T& value) noexcept {
    if (size == capacity) {
      size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
      std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);

      for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
      }

      data = std::move(new_data);
      capacity = new_capacity;
    }

    data[size++] = value;
  }

  void Pop() {
    assert(size != 0 && "No elements to pop");
    --size;
  }

  void Insert(size_t index, const T& value) {
    assert(index <= size && "Index out of range");

    if (size == capacity) {
      size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
      std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);

      for (size_t i = 0; i < index; ++i) {
        new_data[i] = data[i];
      }

      new_data[index] = value;

      for (size_t i = index; i < size; ++i) {
        new_data[i + 1] = data[i];
      }

      data = std::move(new_data);
      capacity = new_capacity;
    } else {
      for (size_t i = size; i > index; --i) {
        data[i] = data[i - 1];
      }

      data[index] = value;
    }

    ++size;
  }
};

#endif  // SRC_ARR_H_
