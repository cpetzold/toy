#include "Resources.h"

namespace mg {

  map<char*, GLuint> Resources::textures;

  bool Resources::loadTexture(char* path) {
    if (!Resources::textures[path]) {
      Resources::textures[path] = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
      if (!Resources::textures[path]) {
        return false;
      }
    }

    glBindTexture(GL_TEXTURE_2D, Resources::textures[path]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return true;
  }

}