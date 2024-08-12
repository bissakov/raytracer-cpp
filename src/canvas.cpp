#include "src/canvas.h"

#include <src/file_io.h>
#include <src/utils.h>
#include <string.h>
#include <windows.h>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <string>

Canvas::Canvas() noexcept : width(0), height(0), pixels(nullptr) {}

Canvas::Canvas(const size_t width_, const size_t height_) noexcept
    : width(width_),
      height(height_),
      pixels(std::make_unique<Pixel[]>(width_ * height_)) {
  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      Pixel* pixel = &pixels[row * width + col];
      pixel->x = col;
      pixel->y = row;
      pixel->color = {};
    }
  }
}

Canvas::Canvas(const Canvas& other) noexcept
    : width(other.width),
      height(other.height),
      pixels(std::make_unique<Pixel[]>(other.width * other.height)) {
  std::copy(other.pixels.get(), other.pixels.get() + other.width * other.height,
            pixels.get());
}

Canvas& Canvas::operator=(const Canvas& other) noexcept {
  if (this != &other) {
    pixels = std::make_unique<Pixel[]>(other.width * other.height);
    std::copy(other.pixels.get(),
              other.pixels.get() + other.width * other.height, pixels.get());
  }
  return *this;
}

Pixel Canvas::PixelAt(const size_t pos_x, const size_t pos_y) const noexcept {
  assert(IsPixelInRange(pos_x, pos_y) && "Pixel out of bounds.");
  return pixels[pos_y * width + pos_x];
}

void Canvas::WritePixelColor(const size_t pos_x, const size_t pos_y,
                             const Color& color) const noexcept {
  assert(IsPixelInRange(pos_x, pos_y) && "Pixel out of bounds.");
  Pixel* pixel = &pixels[pos_y * width + pos_x];
  pixel->color = color;
}

bool Canvas::SaveToPPM(const Path& file_path) noexcept {
  HANDLE file_handle =
      CreateFile(file_path.value, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
  if (file_handle == INVALID_HANDLE_VALUE) {
    return false;
  }

  {
    char header[100];
    int header_len = snprintf(header, sizeof(header), "P3\n%zu %zu\n%d\n",
                              width, height, 255);
    if (header_len < 0 || header_len >= sizeof(header)) {
      CloseHandle(file_handle);
      return false;
    }
    if (!WriteLineToFile(file_handle, header)) {
      CloseHandle(file_handle);
      return false;
    }
  }

  const size_t buffer_size = width * (3 * 4 + 1);
  char* buffer = new char[buffer_size];

  for (size_t row = 0; row < height; ++row) {
    size_t buffer_pos = 0;

    for (size_t col = 0; col < width; ++col) {
      Color* color = &pixels[row * width + col].color;
      size_t red = Clamp(static_cast<size_t>(color->r * 255.0), 0, 255);
      size_t green = Clamp(static_cast<size_t>(color->g * 255.0), 0, 255);
      size_t blue = Clamp(static_cast<size_t>(color->b * 255.0), 0, 255);

      int written = snprintf(buffer + buffer_pos, buffer_size - buffer_pos,
                             "%zu %zu %zu", red, green, blue);
      if (written < 0 || written >= buffer_size - buffer_pos) {
        delete[] buffer;
        CloseHandle(file_handle);
        return false;
      }

      buffer_pos += written;
      if (col < width - 1) {
        buffer[buffer_pos++] = ' ';
      }
    }
    buffer[buffer_pos++] = '\n';
    buffer[buffer_pos] = '\0';

    if (!WriteLineToFile(file_handle, buffer)) {
      delete[] buffer;
      CloseHandle(file_handle);
      return false;
    }
  }

  delete[] buffer;
  CloseHandle(file_handle);

  return true;
}

static inline void AdvanceUntil(char* file_content, uint32_t* idx,
                                const char terminator) {
  while (file_content[*idx] != terminator) {
    (*idx)++;
  }
  (*idx)++;
}

static inline size_t StringToInt(char* start, const size_t length) {
  char* str = new char[length + 1];
  std::copy(start, start + length, str);
  str[length] = '\0';

  size_t res = static_cast<size_t>(std::stoi(str));
  delete[] str;
  return res;
}

static inline bool IsDigit(const char c) {
  return c >= '0' && c <= '9';
}

bool Canvas::LoadFromPPM(const Path& file_path) noexcept {
  if (GetFileAttributesA(file_path.value) == INVALID_FILE_ATTRIBUTES) {
    return false;
  }

  FileResult result = ReadEntireFile(file_path.value);
  char* source = reinterpret_cast<char*>(result.content.get());

  size_t start = 0;
  uint32_t current = 0;

  {
    size_t row = 0;
    for (size_t i = 0; i < 3; ++i) {
      start = current;

      if (row == 1) {
        AdvanceUntil(source, &current, ' ');

        width = StringToInt(source + start, current - start);
        start = current;

        AdvanceUntil(source, &current, '\n');

        height = StringToInt(source + start, current - start);

      } else {
        AdvanceUntil(source, &current, '\n');
      }

      row++;
    }
  }

  start = current;

  pixels = std::make_unique<Pixel[]>(width * height);
  for (size_t row = 0; row < height; ++row) {
    size_t col = 0;
    ColorRGB rgb_color = {};

    while (col <= width - 1) {
      if (source[current] == '\0') {
        break;
      }

      if (IsDigit(source[current])) {
        current++;
        continue;
      }

      if (rgb_color.r == SIZE_MAX) {
        rgb_color.r = StringToInt(source + start, current - start);
        start = current;
      } else if (rgb_color.g == SIZE_MAX) {
        rgb_color.g = StringToInt(source + start, current - start);
        start = current;
      } else if (rgb_color.b == SIZE_MAX) {
        rgb_color.b = StringToInt(source + start, current - start);
        start = current;

        Pixel* current_pixel = &pixels[row * width + col];
        current_pixel->x = col;
        current_pixel->y = row;

        current_pixel->color = {};
        current_pixel->color.r = static_cast<float>(rgb_color.r) / 255.0f;
        current_pixel->color.g = static_cast<float>(rgb_color.g) / 255.0f;
        current_pixel->color.b = static_cast<float>(rgb_color.b) / 255.0f;

        col++;
        rgb_color = {};
      }
      current++;
    }

    current++;
  }

  return height > 0 && width > 0;
}
