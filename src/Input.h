#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <string>
#include <map>
using namespace std;

#include "Vec.h"

namespace mg {
  class Input {
    public:
      static map<int, bool> keysDown;
      static map<int, bool> keysPressed;
      static map<int, bool> keysReleased;

      static bool closed;

      static void init();

      static void poll();
      static void clear();

      static bool keyPressed(int key);
      static bool keyReleased(int key);
      static bool keyDown(int key);

      static bool mouseDown(int button);
      static Vec mousePos();
  };
}

#endif