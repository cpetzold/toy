#ifndef COLOR_H
#define COLOR_H

#include <OpenGL/gl.h>
#include <string>
using namespace std;

namespace mg {
  class Color {
    public:
      GLfloat r, g, b, a;

      Color(GLfloat r = 0.0, GLfloat g = 0.0, GLfloat b = 0.0, GLfloat a = 1.0);
      Color(string hex);

      void setRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
      void setRGB(GLfloat r, GLfloat g, GLfloat b);
      void setHEX(string hex);
  };
}

#endif