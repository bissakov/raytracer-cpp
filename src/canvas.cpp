#include "src/canvas.h"

#include <src/file_io.h>
#include <src/utils.h>
#include <windows.h>

#include <cassert>
#include <string>

Canvas::Canvas(const int width_, const int height_) {
  width = width_;
  height = height_;

  assert(width >= 0 && height >= 0 && "Dimensions must be positive or 0.");

  if (width == 0 && height == 0) {
    pixels = nullptr;
    return;
  }

  pixels = new Pixel*[height];
  for (int row = 0; row < height; ++row) {
    pixels[row] = new Pixel[width];
    for (int col = 0; col < width; ++col) {
      Pixel* pixel = &pixels[row][col];
      pixel->x = col;
      pixel->y = row;
      pixel->color = {};
    }
  }
}

Canvas::~Canvas() {
  if ((width == 0 && height == 0) || pixels == nullptr) {
    return;
  }

  for (int row = 0; row < height; ++row) {
    if (pixels[row] == nullptr) {
      delete[] pixels[row];
    }
  }
  delete[] pixels;
}

bool Canvas::IsPixelInRange(const int pos_x, const int pos_y) const {
  return (pos_x >= 0 && pos_x < width) && (pos_y >= 0 && pos_y < height);
}

Pixel Canvas::PixelAt(const int pos_x, const int pos_y) const {
  assert(IsPixelInRange(pos_x, pos_y) && "Pixel out of bounds.");
  Pixel pixel = pixels[pos_y][pos_x];
  return pixel;
}

void Canvas::WritePixelColor(const int pos_x, const int pos_y,
                             const Color& color) const {
  assert(IsPixelInRange(pos_x, pos_y) && "Pixel out of bounds.");
  Pixel* pixel = &pixels[pos_y][pos_x];
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
//   const int max_rows = 4;
//   const int max_cols = 5;
//
//   char colors[1024];
//   for (int j = 0; j < height; ++j) {
//     for (int i = 0; i < width; ++i) {
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

  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      Color* color = &pixels[j][i].color;
      int red = Clamp(static_cast<int>(color->r * 255.0f), 0, 255);
      int green = Clamp(static_cast<int>(color->g * 255.0f), 0, 255);
      int blue = Clamp(static_cast<int>(color->b * 255.0f), 0, 255);

      canvas_buffer += std::to_string(red) + " " + std::to_string(green) + " " +
                       std::to_string(blue);
      if (i < width - 1) {
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

static inline int StringToInt(char* start, const int length) {
  std::string str = "";
  for (int i = 0; i < length; ++i) {
    str += *GetElement<char>(start, length, i);
  }
  int res = std::stoi(str);
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
  char* source = reinterpret_cast<char*>(result.content);

  int start = 0;
  uint32_t current = 0;

  {
    int row = 0;
    for (int i = 0; i < 3; ++i) {
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

  if (pixels != nullptr) {
    delete[] pixels;
  }

  pixels = new Pixel*[height];
  for (int row = 0; row < height; ++row) {
    pixels[row] = new Pixel[width];

    int col = 0;
    ColorRGB rgb_color = {};

    while (col <= width - 1) {
      if (source[current] == '\0') {
        break;
      }

      if (IsDigit(source[current])) {
        current++;
        continue;
      }

      if (rgb_color.r == -1) {
        rgb_color.r = StringToInt(source + start, current - start);
        start = current;
      } else if (rgb_color.g == -1) {
        rgb_color.g = StringToInt(source + start, current - start);
        start = current;
      } else if (rgb_color.b == -1) {
        rgb_color.b = StringToInt(source + start, current - start);
        start = current;

        Pixel* current_pixel = &pixels[row][col];
        current_pixel->x = col;
        current_pixel->y = row;

        current_pixel->color = {};
        current_pixel->color.r = rgb_color.r / 255.0f;
        current_pixel->color.g = rgb_color.g / 255.0f;
        current_pixel->color.b = rgb_color.b / 255.0f;

        col++;
        rgb_color = {};
      }
      current++;
    }

    current++;
  }

  return height > 0 && width > 0;
}
