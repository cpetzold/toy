#include "Draw.h"

#include <iostream>
using namespace std;

namespace mg {
  namespace draw {

    void rect(GLfloat x, GLfloat y, GLfloat w, GLfloat h, Color c) {
      glPushMatrix();
      glTranslatef(x, y, 0);

      glBegin(GL_QUADS);
      glColor4f(c.r, c.g, c.b, c.a);

      glVertex2f(0, 0);
      glVertex2f(w, 0);
      glVertex2f(w, h);
      glVertex2f(0, h);

      glEnd();
      glPopMatrix();
    }

  }
}