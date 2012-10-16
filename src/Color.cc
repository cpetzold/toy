#include "Color.h"

namespace mg {

  Color::Color(int r, int g, int b, int a) {
    this->setRGBA(r, g, b, a);
  }

  Color::Color(string hex) {

  }

  void Color::setRGBA(int r, int g, int b, int a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  void Color::setRGB(int r, int g, int b) {
    this->setRGBA(r, g, b);
  }

  void Color::setHEX(string hex) {
    
  }

}