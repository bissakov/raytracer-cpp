#ifndef SRC_STR_H_
#define SRC_STR_H_

#include <algorithm>
#include <cstring>
#include <memory>
#include <string>
#include <utility>

struct String {
  size_t length;
  std::unique_ptr<char[]> c_str;

  String() noexcept : length(0), c_str(nullptr) {}

  explicit String(const size_t length_) noexcept
      : length(length_), c_str(std::make_unique<char[]>(length)) {}

  explicit String(const char* str) noexcept
      : length(strlen(str)), c_str(std::make_unique<char[]>(length)) {
    std::copy(str, str + length, c_str.get());
  }
  explicit String(char* str) noexcept
      : length(strlen(str)), c_str(std::make_unique<char[]>(length)) {
    std::copy(str, str + length, c_str.get());
  }

  String& operator=(char* str) noexcept;

  String(const String& other) noexcept
      : length(other.length), c_str(std::make_unique<char[]>(other.length)) {
    std::copy(other.c_str.get(), other.c_str.get() + other.length, c_str.get());
  }

  String(String&& other) noexcept
      : length(other.length), c_str(std::move(other.c_str)) {
    other.length = 0;
  }

  explicit String(std::string other) noexcept
      : length(other.size()), c_str(std::make_unique<char[]>(other.size())) {
    std::copy(other.c_str(), other.c_str() + other.size(), c_str.get());
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
