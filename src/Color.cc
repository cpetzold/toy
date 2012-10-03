#include "Color.h"

namespace mg {

  Color::Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    this->setRGBA(r, g, b, a);
  }

  Color::Color(string hex) {

  }

  void Color::setRGBA(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    this->r = r / 255.0;
    this->g = g / 255.0;
    this->b = b / 255.0;
    this->a = a;
  }

  void Color::setRGB(GLfloat r, GLfloat g, GLfloat b) {
    this->setRGBA(r, g, b);
  }

  void Color::setHEX(string hex) {
    
  }

}