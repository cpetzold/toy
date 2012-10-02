#ifndef GAME_H
#define GAME_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GL/glfw.h>

#include <string>
using namespace std;

namespace mg {
  class Game {
    string name;
    int width;
    int height;
    bool paused;

    public:
      Game(const string &name, int w, int h);
      void init();
      void run();
      void quit(int code);

      void update(double dt);
      void render(double dt);
      void draw(double dt);
  };
}

#endif