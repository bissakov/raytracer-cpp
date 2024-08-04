#ifndef SRC_STR_H_
#define SRC_STR_H_

#include <algorithm>
#include <cstring>
#include <string>

struct String {
  size_t length;
  char* c_str;

  String() noexcept : length(0), c_str(nullptr) {}

  explicit String(const size_t length_) noexcept
      : length(length_), c_str(new char[length]) {}

  explicit String(const char* str) noexcept;
  explicit String(char* str) noexcept;

  String& operator=(char* str) noexcept;
  String(const String& other) noexcept
      : length(other.length), c_str(new char[length]) {
    std::copy(other.c_str, other.c_str + other.length, c_str);
  }
  explicit String(std::string other) noexcept
      : length(other.size()), c_str(new char[length]) {
    std::copy(other.c_str(), other.c_str() + other.size(), c_str);
  }

  ~String() noexcept {
    delete[] c_str;
  }

  String& operator=(const String& other) noexcept;

  String operator+(const String& other) noexcept;
  String operator+(const char* other) noexcept;
  String operator+(char* other) noexcept;

  String operator+=(const String& other) noexcept;
  String operator+=(const char* other) noexcept;

  bool operator==(const String& other) const noexcept;
  bool operator!=(const String& other) const noexcept;
  bool operator==(const char* other) const noexcept;
  bool operator!=(const char* other) const noexcept;
};

#endif  // SRC_STR_H_
