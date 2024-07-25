#ifndef SRC_COLOR_H_
#define SRC_COLOR_H_

struct Color {
  float red;
  float green;
  float blue;

  Color operator+(const Color& other) const;
  Color operator-(const Color& other) const;
  Color operator*(const Color& other) const;

  bool operator==(const Color& other) const;
  bool operator!=(const Color& other) const;

  Color operator*(const float scalar) const;
  Color operator/(const float scalar) const;
};

#endif  // SRC_COLOR_H_
