#define BUILDING_NODE_EXTENSION

#include <node.h>
// using namespace v8;

#include "Game.h"
#include "Vec.h"
using namespace mg;

void init(Handle<Object> target) {
  Game::bind(target);
  Vec::bind(target);
}

NODE_MODULE(toy, init);