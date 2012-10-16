#include "Game.h"
#include "Input.h"

#include <iostream>
using namespace std;

namespace mg {

  Persistent<Function> Game::constructor;

  Handle<Value> Game::newFunc(const Arguments& args) {
    HandleScope scope;

    String::Utf8Value name(args[0]->ToString());

    Game* g = new Game(string(*name), args[1]->IntegerValue(), args[2]->IntegerValue());
    g->Wrap(args.This());
    return args.This();
  }

  void Game::bind(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(Game::newFunc);
    tpl->SetClassName(String::NewSymbol("Game"));

    Local<ObjectTemplate> instance = tpl->InstanceTemplate();
    instance->SetInternalFieldCount(1);
    // instance->SetAccessor(String::New("x"), Vec::getX, Vec::setX);
    // instance->SetAccessor(String::New("y"), Vec::getY, Vec::setY);

    Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
    proto->Set(String::NewSymbol("init"), FunctionTemplate::New(Game::init_)->GetFunction());
    proto->Set(String::NewSymbol("run"), FunctionTemplate::New(Game::run_)->GetFunction());

    Game::constructor = Persistent<Function>::New(tpl->GetFunction());
    target->Set(String::NewSymbol("Game"), constructor);
  }

  Game::Game(const string &name, int w, int h) {
    this->name = name;
    this->width = w;
    this->height = h;
    this->paused = false;
    this->window = NULL;
    this->renderer = NULL;
  }

  void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      this->quit(1);
    }

    this->window = SDL_CreateWindow(
      this->name.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      this->width,
      this->height,
      SDL_WINDOW_SHOWN
    );

    if (this->window == NULL) {
      this->quit(1);
    }

    this->renderer = SDL_CreateRenderer(
      this->window,
      -1,
      SDL_RENDERER_ACCELERATED
    );

    if (this->renderer == NULL) {
      this->quit(1);
    }

    Color black;
    this->setBackgroundColor(black);

    SDL_RenderPresent(this->renderer);

    this->input = new Input;
    Input::init();
  }

  Handle<Value> Game::init_(const Arguments& args) {
    HandleScope scope;
    Game* g = ObjectWrap::Unwrap<Game>(args.This());
    g->init();
    return scope.Close(args.This());
  }

  void Game::resize(int width, int height) {
    //glfwSetWindowSize(width, height);
  }

  void Game::setBackgroundColor(Color& c) {
    SDL_SetRenderDrawColor(this->renderer, c.r, c.g, c.b, c.a);
    this->clear();
  }

  void Game::clear() {
    SDL_RenderClear(this->renderer);
  }

  void Game::run() {
    this->init();

    const double dt = 0.01;
    uint64_t currentTime = SDL_GetPerformanceCounter();
    double accumulator = 0;

    while (true) {
      if (Input::closed) {
        this->quit(1);
      }

      uint64_t newTime = SDL_GetPerformanceCounter();
      double frameTime = (newTime - currentTime) / double(SDL_GetPerformanceFrequency());

      if (frameTime > 0.1) {
        frameTime = 0.1;
      }

      currentTime = newTime;
      accumulator += frameTime;

      // cout << frameTime << " - " << accumulator << endl;

      while (accumulator >= dt) {
        // cout << "polling" << endl;
        Input::poll();

        // this->handleInput(dt);
        // if (!this->paused) {
        //   this->update(dt);
        // }

        Input::clear();
        accumulator -= dt;
      }

      this->render(dt);
      SDL_Delay(1);
    }
  }

  Handle<Value> Game::run_(const Arguments& args) {
    HandleScope scope;
    Game* g = ObjectWrap::Unwrap<Game>(args.This());
    g->run();
    return scope.Close(args.This());
  }

  void Game::quit(int code) {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
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
  }

  void Game::update(double dt) {
    
    list<Sprite*>::iterator it;
    for (unsigned int i = 0; i < 10; i++) {
      for (it = this->layers[i].begin(); it != this->layers[i].end(); ++it) {
        (*it)->update(dt);
      }
    }
  }

  void Game::render(double dt) {
    this->clear();
    // this->draw(dt);
    SDL_RenderPresent(this->renderer);
  }

  void Game::draw(double dt) {

    list<Sprite*>::iterator it;
    for (unsigned int i = 0; i < 10; i++) {
      for (it = this->layers[i].begin(); it != this->layers[i].end(); ++it) {
        (*it)->draw(dt);
      }
    }
  }

}