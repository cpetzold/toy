#ifndef RESOURCES_H
#define RESOURCES_H

#include <OpenGL/gl.h>
#include <SOIL.h>
#include <map>
using namespace std;

namespace mg {
  class Resources {
    public:
      static map<char*, GLuint> textures;

      static bool loadTexture(char* path);
  };
}

#endif