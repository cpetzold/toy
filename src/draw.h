#ifndef DRAW_H
#define DRAW_H

#include <OpenGL/gl.h>
#include "Color.h"

namespace mg {
  namespace draw {

    void rect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, Color c = Color(255.0, 255.0, 255.0));

  }
}

#endif