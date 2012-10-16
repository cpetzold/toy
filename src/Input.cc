#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  map<int, bool> Input::keysDown;
  map<int, bool> Input::keysPressed;
  map<int, bool> Input::keysReleased;
  bool Input::closed = false;

  void Input::init() {

  }

  void Input::poll() {
    SDL_Event event; 

    while (SDL_PollEvent(&event)) { 
      switch (event.type) {
        case SDL_KEYDOWN:
          Input::keysPressed[event.key.keysym.sym] = true;
          Input::keysDown[event.key.keysym.sym] = true;
          break;
        case SDL_KEYUP:
          Input::keysReleased[event.key.keysym.sym] = true;
          Input::keysDown[event.key.keysym.sym] = false;
          break;
        case SDL_MOUSEMOTION:
          break;
        case SDL_WINDOWEVENT: 
          switch (event.window.event) { 
            case SDL_WINDOWEVENT_CLOSE: 
              Input::closed = true;
              break; 
          } 
          break; 
      } 
    } 
  }

  void Input::clear() {
    Input::keysPressed.clear();
    Input::keysReleased.clear();
  }

  bool Input::keyPressed(int key) {
    return Input::keysPressed[key];
  }

  bool Input::keyReleased(int key) {
    return Input::keysReleased[key];
  }

  bool Input::keyDown(int key) {
    return Input::keysDown[key];
  }

  bool Input::mouseDown(int button) {
    
  }

  Vec Input::mousePos() {
    int x = 0;
    int y = 0;

    return Vec(x, y);
  }

}