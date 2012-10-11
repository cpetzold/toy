#ifndef VEC_H
#define VEC_H

#include <OpenGL/gl.h>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

#include <node.h>
using namespace v8;
using namespace node;

namespace mg {

  class Vec: public ObjectWrap {
    public:
      GLfloat x, y;

      Vec(GLfloat x = 0, GLfloat y = 0): x(x), y(y) {};
      ~Vec() {};

      static void init(Handle<Object> target);
      
      static Handle<Value> getX(Local<String> property, const AccessorInfo &info);
      static void setX(Local<String> property, Local<Value> value, const AccessorInfo& info);
      
      static Handle<Value> getY(Local<String> property, const AccessorInfo &info);
      static void setY(Local<String> property, Local<Value> value, const AccessorInfo& info);

      static Handle<Value> print(const Arguments& args);
      
      void operator=(const Vec &v);
      // static Handle<Value> 
      
      Vec operator*(GLfloat scalar) const;
      void operator*=(const Vec &v);
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

    private:
      static Handle<Value> newFunc(const Arguments& args);
      
  };

}

#endif