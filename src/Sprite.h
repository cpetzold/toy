#ifndef SPRITE_H
#define SPRITE_H

#include <OpenGL/gl.h>
#include <string>
using namespace std;

#include "Vec.h"
#include "draw.h"

namespace mg {
  class Sprite {
    public:
      Vec pos;

      Sprite(GLfloat x, GLfloat y);
      Sprite(Vec pos);

      virtual void update(GLdouble dt);
      virtual void draw(GLdouble dt) const;
  };
}

#endif