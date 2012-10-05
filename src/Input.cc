#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  map<GLint, bool> Input::keysPressed;
  map<GLint, bool> Input::keysReleased;

  void GLFWCALL keyCallbackWrapper(GLint key, GLint action) {
    Input::handleKey(key, action);
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

  void Input::handleKey(GLint key, GLint action) {
    if (action == GLFW_PRESS) {
      Input::keysPressed[key] = true;
    } else {
      Input::keysReleased[key] = true;
    }
  }

  bool Input::keyPressed(GLint key) {
    return Input::keysPressed[key];
  }

  bool Input::keyReleased(GLint key) {
    return Input::keysReleased[key];
  }

  bool Input::keyDown(GLint key) {
    return glfwGetKey(key) == GLFW_PRESS; 
  }

  bool Input::mouseDown(int button) {
    return glfwGetMouseButton(button);
  }

}