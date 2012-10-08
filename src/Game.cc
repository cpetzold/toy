#include "Game.h"
#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  static int GLFWCALL closeCallbackWrapper();
  static void GLFWCALL resizeCallbackWrapper(int width, int height);

  Game* Game::instance;

  Game::Game(const string &name, GLint w, GLint h) {
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
    return 1;
  }

  static void GLFWCALL resizeCallbackWrapper(GLint width, GLint height) {
    Game::instance->handleResize(width, height);
  }

  void Game::resize(GLint width, GLint height) {
    glfwSetWindowSize(width, height);
  }

  void Game::setBackgroundColor(Color& c) {
    glClearColor(c.r, c.g, c.b, c.a);
  }

  void Game::run() {
    const GLdouble dt = 0.01;
    GLdouble currentTime = glfwGetTime();
    GLdouble accumulator = 0.0;

    while (true) {
      GLdouble newTime = glfwGetTime();
      GLdouble frameTime = newTime - currentTime;
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

  void Game::quit(GLint code) {
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

  void Game::handleInput(GLdouble dt) {

  }

  void Game::handleClose() {
    this->quit(0);
  }

  void Game::handleResize(GLint width, GLint height) {
    this->width = width;
    this->height = height;

    glViewport(0, 0, this->width, this->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, this->width, this->height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  void Game::update(GLdouble dt) {
    
    list<Sprite*>::iterator it;
    for (unsigned int i = 0; i < 10; i++) {
      for (it = this->layers[i].begin(); it != this->layers[i].end(); ++it) {
        (*it)->update(dt);
      }
    }
  }

  void Game::render(GLdouble dt) {
    glClear(GL_COLOR_BUFFER_BIT);
    this->draw(dt);
    glfwSwapBuffers();
  }

  void Game::draw(GLdouble dt) {

    list<Sprite*>::iterator it;
    for (unsigned int i = 0; i < 10; i++) {
      for (it = this->layers[i].begin(); it != this->layers[i].end(); ++it) {
        (*it)->draw(dt);
      }
    }
  }

}