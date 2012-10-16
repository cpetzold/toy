#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <string>
#include <list>
using namespace std;

#include <node.h>

#include "Input.h"
#include "Color.h"
#include "Sprite.h"

namespace mg {
  class Game : public ObjectWrap {
    public:
      string name;
      int width, height;
      bool paused;
      Input* input;

      SDL_Window* window;
      SDL_Renderer* renderer;
      list<Sprite*> layers[10];

      static void bind(Handle<Object> target);

      Game(const string &name, int w, int h);

      virtual void init();
      static Handle<Value> init_(const Arguments& args);
      virtual void run();
      static Handle<Value> run_(const Arguments& args);
      virtual void quit(int code);

      void resize(int width, int height);
      void handleResize();
      void setBackgroundColor(Color& c);
      void clear();

      virtual void pause();
      virtual void unpause();
      virtual void togglePause();

      virtual void handleClose();
      virtual void handleInput(double dt);
      virtual void handleResize(int width, int height);

      virtual void update(double dt);
      virtual void render(double dt);
      virtual void draw(double dt);

    private:
      static Persistent<Function> constructor;
      static Handle<Value> newFunc(const Arguments& args);
  };
}

#endif