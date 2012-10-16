#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
using namespace std;

namespace mg {
  class Resources {
    public:
      static map<char*, int> textures;

      static bool loadTexture(char* path);
  };
}

#endif