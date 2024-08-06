#include <src/str.h>

String::String(const char* str) noexcept
    : length(strlen(str)), c_str(new char[length]) {
  for (size_t i = 0; i < length; ++i) {
    c_str[i] = str[i];
  }
}

String::String(char* str) noexcept
    : length(strlen(str)), c_str(new char[length]) {
  for (size_t i = 0; i < length; ++i) {
    c_str[i] = str[i];
  }
}

String& String::operator=(char* str) noexcept {
  if (c_str != nullptr) {
    delete[] c_str;
  }
  length = strlen(str);
  c_str = new char[length];
  for (size_t i = 0; i < length; ++i) {
    c_str[i] = str[i];
  }

  return *this;
}

String& String::operator=(const String& other) noexcept {
  if (this != &other) {
    if (c_str != nullptr) {
      delete[] c_str;
    }

    if (other.c_str != nullptr) {
      c_str = new char[other.length + 1];
      for (size_t i = 0; i < other.length; ++i) {
        c_str[i] = other.c_str[i];
      }
      c_str[other.length] = '\0';
    } else {
      c_str = nullptr;
    }
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
