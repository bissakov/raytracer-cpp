#include <src/str.h>

#include <algorithm>
#include <memory>

String& String::operator=(char* str) noexcept {
  length = strlen(str);
  c_str = std::make_unique<char[]>(length);
  std::copy(str, str + length, c_str.get());
  return *this;
}

String& String::operator=(const String& other) noexcept {
  if (this != &other) {
    length = other.length;
    c_str = std::make_unique<char[]>(other.length);
    std::copy(other.c_str.get(), other.c_str.get() + other.length, c_str.get());
  }
  return *this;
}

String String::operator+(const String& other) noexcept {
  String str = String{length + other.length};

  for (size_t i = 0; i < length; ++i) {
    str.c_str[i] = c_str[i];
  }

  for (size_t i = 0; i < other.length; ++i) {
    str.c_str[i + length] = other.c_str[i];
  }

  return str;
}

String String::operator+(const char* other) noexcept {
  size_t other_length = strlen(other);
  String str = String{length + other_length};

  for (size_t i = 0; i < length; ++i) {
    str.c_str[i] = c_str[i];
  }

  for (size_t i = 0; i < other_length; ++i) {
    str.c_str[i + length] = other[i];
  }

  return str;
}

String String::operator+(char* other) noexcept {
  size_t other_length = strlen(other);
  String str = String{length + other_length};

  for (size_t i = 0; i < length; ++i) {
    str.c_str[i] = c_str[i];
  }

  for (size_t i = 0; i < other_length; ++i) {
    str.c_str[i + length] = other[i];
  }

  return str;
}

String String::operator+=(const String& other) noexcept {
  return *this + other;
}
String String::operator+=(const char* other) noexcept {
  return *this + other;
}

bool String::operator==(const String& other) const noexcept {
  if (length != other.length) {
    return false;
  }

  for (size_t i = 0; i < length; ++i) {
    if (c_str[i] != other.c_str[i]) {
      return false;
    }
  }

  return true;
}

bool String::operator!=(const String& other) const noexcept {
  return !(*this == other);
}

bool String::operator==(const char* other) const noexcept {
  if (length != strlen(other)) {
    return false;
  }

  for (size_t i = 0; i < length; ++i) {
    if (c_str[i] != other[i]) {
      return false;
    }
  }

  return true;
}
bool String::operator!=(const char* other) const noexcept {
  return !(*this == other);
}
