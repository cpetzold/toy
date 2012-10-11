#define BUILDING_NODE_EXTENSION

#include <node.h>
using namespace v8;

#include "Vec.h"
using namespace mg;

void init(Handle<Object> target) {
  Vec::init(target);
}

NODE_MODULE(toy, init);