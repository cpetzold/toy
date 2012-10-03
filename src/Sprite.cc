#include "Sprite.h"

namespace mg {

  Sprite::Sprite(GLfloat x, GLfloat y) {
    this->pos = Vec(x, y);
  }

  Sprite::Sprite(Vec pos) {
    this->pos = pos;
  }

  void Sprite::update(GLdouble dt) {

  }

  void Sprite::draw(GLdouble dt) const {
    
  }

}
