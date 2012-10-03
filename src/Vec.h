#ifndef VEC_H
#define VEC_H

#include <OpenGL/gl.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

namespace mg {

  class Vec {  
    public:
      GLfloat x, y;
      
      Vec(GLfloat x = 0, GLfloat y = 0): x(x), y(y) {};
      ~Vec() {};
      
      Vec operator*(GLfloat scalar) const;
      void operator*=(GLfloat scalar);
      
      Vec operator/(GLfloat scalar) const;
      
      Vec operator+(const Vec &v) const;
      void operator+=(const Vec &v);
      
      Vec operator-(const Vec &v) const;
      void operator-=(const Vec &v);
      
      bool operator<(const Vec &v);
      bool operator<=(const Vec &v);
      bool operator>(const Vec &v);
      bool operator>=(const Vec &v);
      
      void set(GLfloat x, GLfloat y);
      
      void rotate(GLfloat angle);
      
      float cross(const Vec &v) const;
      float dot(const Vec &v) const;
      
      float magnitude();
      void normalize();
      
      Vec randCenter(const Vec &v);
  };

}

#endif