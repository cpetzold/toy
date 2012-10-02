#include "Game.h"
#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  Game::Game(const string &name, int w, int h) {
    this->name = name;
    this->width = w;
    this->height = h;

    this->paused = false;
  }

  void Game::init() {
    if (glfwInit() != GL_TRUE) {
      this->quit(1);
    }

    if (glfwOpenWindow(this->width, this->height, 5, 6, 5, 0, 8, 0, GLFW_WINDOW) != GL_TRUE) {
      this->quit(1);
    }

    glfwSetWindowTitle(this->name.c_str());

    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width, this->height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    this->input = new Input;
    Input::init();
  }

  void Game::run() {
    const double dt = 0.01;
    double currentTime = glfwGetTime();
    double accumulator = 0.0;

    while (!this->paused) {
      double newTime = glfwGetTime();
      double frameTime = newTime - currentTime;
      if (frameTime > 0.25) {
        frameTime = 0.25;
      }

      currentTime = newTime;
      accumulator += frameTime;

      while (accumulator >= dt) {
        Input::poll();
        this->update(dt);
        Input::clear();
        accumulator -= dt;
      }

      this->render(dt);
    }
  }

  void Game::render(double dt) {
    glClear(GL_COLOR_BUFFER_BIT);
    this->draw(dt);
    glfwSwapBuffers();
  }

  void Game::draw(double dt) {
    
  }

  void Game::update(double dt) {
    
  }

  void Game::quit(int code) {
    glfwTerminate();
    exit(code);
  }

}