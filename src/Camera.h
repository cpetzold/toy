#ifndef CAMERA_H
#define CAMERA_H

#include <OpenGL/gl.h>
#include <string>
using namespace std;

#include "Vec.h"

namespace mg {
  class Camera {
    public:
      Vec dim, pos;

      Camera(Vec dim = Vec(800, 600), Vec pos = (0, 0));

      
      
  };
}

#endif