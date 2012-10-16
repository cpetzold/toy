#ifndef COLOR_H
#define COLOR_H

#include <OpenGL/gl.h>
#include <string>
using namespace std;

namespace mg {
  class Color {
    public:
      int r, g, b, a;

      Color(int r = 0, int g = 0, int b = 0, int a = 255);
      Color(string hex);

      void setRGBA(int r, int g, int b, int a = 255);
      void setRGB(int r, int g, int b);
      void setHEX(string hex);
  };
}

#endif