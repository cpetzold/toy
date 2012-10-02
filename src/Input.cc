#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  map<int, bool> Input::keysPressed;
  map<int, bool> Input::keysReleased;

  void GLFWCALL keyCallbackWrapper(int key, int action) {
    Input::keyCallback(key, action);
  }

  void Input::init() {
    glfwSetKeyCallback(keyCallbackWrapper);
  }

  void Input::poll() {
    glfwPollEvents();
  }

  void Input::clear() {
    Input::keysPressed.clear();
    Input::keysReleased.clear();
  }

  void Input::keyCallback(int key, int action) {
    if (action == GLFW_PRESS) {
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
    return glfwGetKey(key) == GLFW_PRESS; 
  }

}