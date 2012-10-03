#ifndef INPUT_H
#define INPUT_H

#include <GL/glfw.h>
#include <string>
#include <map>
using namespace std;

namespace mg {
  class Input {
    public:
      static map<int, bool> keysPressed;
      static map<int, bool> keysReleased;

      static void init();

      static void poll();
      static void clear();

      static void handleKey(int key, int action);

      static bool keyPressed(int key);
      static bool keyReleased(int key);
      static bool keyDown(int key);
  };
}

#endif