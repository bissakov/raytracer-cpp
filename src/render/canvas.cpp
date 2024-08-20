#include <core/file_io.h>
#include <core/utils.h>
#include <render/canvas.h>
#include <string.h>
#include <windows.h>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <format>
#include <memory>
#include <string>

Canvas::Canvas() noexcept : width(0), height(0), colors(nullptr) {}

Canvas::Canvas(const size_t width, const size_t height) noexcept
    : width(width),
      height(height),
      colors(std::make_unique<Color[]>(width * height)) {}

Canvas::Canvas(const Canvas& other) noexcept
    : width(other.width),
      height(other.height),
      colors(std::make_unique<Color[]>(other.width * other.height)) {
  std::copy(other.colors.get(), other.colors.get() + other.width * other.height,
            colors.get());
}

Canvas& Canvas::operator=(const Canvas& other) noexcept {
  if (this != &other) {
    colors = std::make_unique<Color[]>(other.width * other.height);
    std::copy(other.colors.get(),
              other.colors.get() + other.width * other.height, colors.get());
  }
  return *this;
}

Color Canvas::ColorAt(const size_t pos_x, const size_t pos_y) const noexcept {
  assert(IsInRange(pos_x, pos_y) && "Color out of bounds.");
  return colors[pos_y * width + pos_x];
}

void Canvas::WriteColor(const size_t pos_x, const size_t pos_y,
                        const Color& color) const noexcept {
  assert(IsInRange(pos_x, pos_y) && "Color out of bounds.");
  colors[pos_y * width + pos_x] = color;
}

bool Canvas::SaveToPPM(const Path& file_path) const noexcept {
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
  auto buffer = std::make_unique<char[]>(buffer_size);

  for (size_t row = 0; row < height; ++row) {
    size_t buffer_pos = 0;

    for (size_t col = 0; col < width; ++col) {
      Color* color = &colors[row * width + col];
      ColorRGB rgb{NormalizedToRGB(*color)};

      int written =
          snprintf(buffer.get() + buffer_pos, buffer_size - buffer_pos,
                   "%d %d %d", rgb.r, rgb.g, rgb.b);
      if (written < 0 || written >= buffer_size - buffer_pos) {
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

    if (!WriteLineToFile(file_handle, buffer.get())) {
      CloseHandle(file_handle);
      return false;
    }
  }

  CloseHandle(file_handle);

  return true;
}

static inline void AdvanceUntil(const char* file_content, uint32_t* idx,
                                const char terminator) {
  while (file_content[*idx] != terminator) {
    (*idx)++;
  }
  (*idx)++;
}

static inline int32_t StringToInt(char* start, const size_t length) {
  char str[50];
  std::copy(start, start + length, str);
  str[length] = '\0';
  int32_t res = static_cast<int32_t>(std::stoi(str));
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

  colors = std::make_unique<Color[]>(width * height);
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

      if (rgb_color.r == INT_MAX) {
        rgb_color.r = StringToInt(source + start, current - start);
        start = current;
      } else if (rgb_color.g == INT_MAX) {
        rgb_color.g = StringToInt(source + start, current - start);
        start = current;
      } else if (rgb_color.b == INT_MAX) {
        rgb_color.b = StringToInt(source + start, current - start);
        start = current;

        Color* current_pixel = &colors[row * width + col];
        current_pixel->r = static_cast<float>(rgb_color.r) / 255.0F;
        current_pixel->g = static_cast<float>(rgb_color.g) / 255.0F;
        current_pixel->b = static_cast<float>(rgb_color.b) / 255.0F;

        col++;
        rgb_color = {};
      }
      current++;
    }

    current++;
  }

  return height > 0 && width > 0;
}
Canvas::operator std::string() const noexcept {
  return std::format("Canvas(width={}, height={})", width, height);
}

std::ostream& operator<<(std::ostream& os, const Canvas& c) {
  os << std::string(c);
  return os;
}
