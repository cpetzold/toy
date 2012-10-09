#ifndef GAME_H
#define GAME_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GL/glfw.h>

#include <string>
#include <list>
using namespace std;

#include "Input.h"
#include "Color.h"
#include "Sprite.h"

namespace mg {
  class Game {
    public:
      string name;
      GLint width;
      GLint height;
      bool paused;
      Input* input;
      list<Sprite*> layers[10];

      static Game* instance;

      Game(const string &name, GLint w, GLint h);
      virtual void init();
      virtual void run();
      virtual void quit(GLint code);

      void resize(GLint width, GLint height);
      void handleResize();
      void setBackgroundColor(Color& c);

      virtual void pause();
      virtual void unpause();
      virtual void togglePause();

      virtual void handleClose();
      virtual void handleInput(GLdouble dt);
      virtual void handleResize(GLint width, GLint height);

      virtual void update(GLdouble dt);
      virtual void render(GLdouble dt);
      virtual void draw(GLdouble dt);
  };
}

#endif