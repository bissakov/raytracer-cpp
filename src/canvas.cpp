#include "src/canvas.h"

#include <cassert>

Canvas::Canvas(int width_, int height_) {
  width = width_;
  height = height_;

  pixels = new Pixel*[height];
  for (int j = 0; j < height; ++j) {
    pixels[j] = new Pixel[width];
    for (int i = 0; i < width; ++i) {
      Pixel* pixel = &pixels[j][i];
      pixel->x = i;
      pixel->y = j;
      pixel->color = {};
    }
  }
}

Canvas::~Canvas() {
  for (int j = 0; j < height; ++j) {
    delete[] pixels[j];
  }
  delete[] pixels;
}

bool Canvas::IsPixelOutOfBounds(const int pos_x, const int pos_y) const {
  return (pos_x >= 0 && pos_x < width) && (pos_y >= 0 && pos_y < height);
}

Pixel Canvas::PixelAt(const int pos_x, const int pos_y) const {
  assert(IsPixelOutOfBounds(pos_x, pos_y) && "Pixel out of bounds.");
  Pixel pixel = pixels[pos_y][pos_x];
  return pixel;
}

void Canvas::WritePixelColor(const int pos_x, const int pos_y,
                             const Color& color) const {
  assert(IsPixelOutOfBounds(pos_x, pos_y) && "Pixel out of bounds.");
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
