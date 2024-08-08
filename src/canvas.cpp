#include "src/canvas.h"

#include <src/file_io.h>
#include <src/utils.h>
#include <windows.h>

#include <cassert>
#include <cstdint>
#include <memory>
#include <string>

Canvas& Canvas::operator=(const Canvas& other) {
  if (this != &other) {
    pixels = std::make_unique<Pixel[]>(other.width * other.height);
    std::copy(other.pixels.get(),
              other.pixels.get() + other.width * other.height, pixels.get());
  }
  return *this;
}

bool Canvas::IsPixelInRange(const size_t pos_x, const size_t pos_y) const {
  return (pos_x < width) && (pos_y < height);
}

Pixel Canvas::PixelAt(const size_t pos_x, const size_t pos_y) const {
  assert(IsPixelInRange(pos_x, pos_y) && "Pixel out of bounds.");
  Pixel pixel = pixels[pos_y * width + pos_x];
  return pixel;
}

void Canvas::WritePixelColor(const size_t pos_x, const size_t pos_y,
                             const Color& color) const {
  assert(IsPixelInRange(pos_x, pos_y) && "Pixel out of bounds.");
  Pixel* pixel = &pixels[pos_y * width + pos_x];
  pixel->color = color;
}

// std::string Canvas::ToString() const {
//   /*
//
//   Canvas{
//     width=1920,
//     height=1080,
//     pixels={
//       #000000 #000000 #000000 #000000 #000000
//       #000000 #000000 #000000 #000000 #000000
//       #000000 #000000 #000000 #000000 #000000
//       #000000 #000000 #000000 #000000 #000000
//     }
//   }
//
//   */
//
//   const size_t max_rows = 4;
//   const size_t max_cols = 5;
//
//   char colors[1024];
//   for (size_t j = 0; j < height; ++j) {
//     for (size_t i = 0; i < width; ++i) {
//     }
//   }
//
//   char canvas_buffer[1024];
//   snprintf(canvas_buffer, sizeof(canvas_buffer),
//            "Canvas{\n  width=%d,\n  height=%d,\n  pixels={\n    #00000 #00000
//            "
//            "#00000\n    #00000 #00000 #00000\n  }\n}",
//            width, height);
//   std::string canvas_str = canvas_buffer;
//   return canvas_str;
// }

bool Canvas::SaveToPPM(const std::string file_path) {
  std::string canvas_buffer = "";
  canvas_buffer +=
      "P3\n" + std::to_string(width) + " " + std::to_string(height) + "\n255\n";

  for (size_t row = 0; row < height; ++row) {
    for (size_t col = 0; col < width; ++col) {
      Color* color = &pixels[row * width + col].color;
      size_t red = Clamp(static_cast<size_t>(color->r * 255.0), 0, 255);
      size_t green = Clamp(static_cast<size_t>(color->g * 255.0), 0, 255);
      size_t blue = Clamp(static_cast<size_t>(color->b * 255.0), 0, 255);

      canvas_buffer += std::to_string(red) + " " + std::to_string(green) + " " +
                       std::to_string(blue);
      if (row < width - 1) {
        canvas_buffer += " ";
      }
    }
    canvas_buffer += "\n";
  }

  bool res = WriteFileText(file_path, canvas_buffer);
  return res;
}

static inline void AdvanceUntil(char* file_content, uint32_t* idx,
                                const char terminator) {
  while (file_content[*idx] != terminator) {
    (*idx)++;
  }
  (*idx)++;
}

static inline size_t StringToInt(char* start, const size_t length) {
  std::string str = "";
  for (size_t i = 0; i < length; ++i) {
    str += *GetElement<char>(start, length, i);
  }
  size_t res = static_cast<size_t>(std::stoi(str));

  return res;
}

static inline bool IsDigit(const char c) {
  return c >= '0' && c <= '9';
}

bool Canvas::LoadFromPPM(const std::string file_path) {
  if (GetFileAttributesA(file_path.c_str()) == INVALID_FILE_ATTRIBUTES) {
    return false;
  }

  FileResult result = ReadEntireFile(file_path);
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
