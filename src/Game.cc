#include "Game.h"
#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  static int GLFWCALL closeCallbackWrapper();
  static void GLFWCALL resizeCallbackWrapper(int width, int height);

  Game* Game::instance;

  Game::Game(const string &name, int w, int h) {
    this->name = name;
    this->width = w;
    this->height = h;
    this->paused = false;
  }

  void Game::init() {
    Game::instance = this;

    if (glfwInit() != GL_TRUE) {
      this->quit(1);
    }

    if (glfwOpenWindow(this->width, this->height, 5, 6, 5, 0, 8, 0, GLFW_WINDOW) != GL_TRUE) {
      this->quit(1);
    }

    glfwSetWindowTitle(this->name.c_str());

    glfwSwapInterval(1);

    glfwSetWindowCloseCallback(closeCallbackWrapper);
    glfwSetWindowSizeCallback(resizeCallbackWrapper);

    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);    

    Color black;
    this->setBackgroundColor(black);

    this->input = new Input;
    Input::init();
  }

  static int GLFWCALL closeCallbackWrapper() {
    Game::instance->handleClose();
  }

  static void GLFWCALL resizeCallbackWrapper(int width, int height) {
    Game::instance->handleResize(width, height);
  }

  void Game::resize(int width, int height) {
    glfwSetWindowSize(width, height);
  }

  void Game::setBackgroundColor(Color& c) {
    glClearColor(c.r, c.g, c.b, c.a);
  }

  void Game::run() {
    const double dt = 0.01;
    double currentTime = glfwGetTime();
    double accumulator = 0.0;

    while (true) {
      double newTime = glfwGetTime();
      double frameTime = newTime - currentTime;
      if (frameTime > 0.25) {
        frameTime = 0.25;
      }

      currentTime = newTime;
      accumulator += frameTime;

      while (accumulator >= dt) {
        Input::poll();

        this->handleInput(dt);
        if (!this->paused) {
          this->update(dt);
        }

        Input::clear();
        accumulator -= dt;
      }

      this->render(dt);
    }
  }

  void Game::quit(int code) {
    glfwTerminate();
    exit(code);
  }

  void Game::pause() {
    this->paused = true;
  }

  void Game::unpause() {
    this->paused = false;
  }

  void Game::togglePause() {
    if (this->paused) {
      this->unpause();
    } else {
      this->pause();
    }
  }

  void Game::handleInput(double dt) {

  }

  void Game::handleClose() {
    this->quit(0);
  }

  void Game::handleResize(int width, int height) {
    this->width = width;
    this->height = height;

    glViewport(0, 0, this->width, this->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, this->width, this->height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void Game::update(double dt) {
    
  }

  void Game::render(double dt) {
    glClear(GL_COLOR_BUFFER_BIT);
    this->draw(dt);
    glfwSwapBuffers();
  }

  void Game::draw(double dt) {
    
  }

}