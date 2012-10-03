#ifndef GAME_H
#define GAME_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GL/glfw.h>

#include <string>
using namespace std;

#include "Input.h"
#include "Color.h"

namespace mg {
  class Game {
    string name;
    int width;
    int height;
    bool paused;

    Input* input;

    public:
      static Game* instance;

      Game(const string &name, int w, int h);
      virtual void init();
      virtual void run();
      virtual void quit(int code);

      void setBackgroundColor(Color& c);

      virtual void pause();
      virtual void unpause();
      virtual void togglePause();

      virtual void handleClose();

      virtual void handleInput(double dt);
      virtual void update(double dt);
      virtual void render(double dt);
      virtual void draw(double dt);
  };
}

#endif