#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  map<int, bool> Input::keysPressed;
  map<int, bool> Input::keysReleased;

  void Input::init() {
    
  }

  void Input::poll() {
    
  }

  void Input::clear() {
    Input::keysPressed.clear();
    Input::keysReleased.clear();
  }

  void Input::handleKey(int key, int action) {
    if (action == 0) {
      Input::keysPressed[key] = true;
    } else {
      Input::keysReleased[key] = true;
    }
  }

  bool Input::keyPressed(int key) {
    return Input::keysPressed[key];
  }

  bool Input::keyReleased(int key) {
    return Input::keysReleased[key];
  }

  bool Input::keyDown(int key) {
    
  }

  bool Input::mouseDown(int button) {
    
  }

  Vec Input::mousePos() {
    int x = 0;
    int y = 0;

    return Vec(x, y);
  }

}