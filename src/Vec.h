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

  class Vec : public ObjectWrap {
    public:
      GLfloat x, y;

      Vec(GLfloat x = 0, GLfloat y = 0): x(x), y(y) {};
      Vec(const Vec &v): x(v.x), y(v.y) {};
      ~Vec() {};

      static void bind(Handle<Object> target);
      
      static Handle<Value> getX(Local<String> property, const AccessorInfo &info);
      static void setX(Local<String> property, Local<Value> value, const AccessorInfo& info);
      
      static Handle<Value> getY(Local<String> property, const AccessorInfo &info);
      static void setY(Local<String> property, Local<Value> value, const AccessorInfo& info);
      
      void operator=(const Vec &v);
      // static Handle<Value> 
      
      Vec operator*(const Vec &v) const;
      Vec operator*(GLfloat scalar) const;
      static Handle<Value> mult(const Arguments& args);

      void operator*=(const Vec &v);
      void operator*=(GLfloat scalar);
      static Handle<Value> multSelf(const Arguments& args);
      
      Vec operator/(GLfloat scalar) const;
      static Handle<Value> div(const Arguments& args);
      
      Vec operator+(const Vec &v) const;
      static Handle<Value> add(const Arguments& args);

      void operator+=(const Vec &v);
      static Handle<Value> addSelf(const Arguments& args);
      
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
      static Persistent<Function> constructor;
      static Handle<Value> newFunc(const Arguments& args);
      // static Handle<Value> newInstance(const Arguments& args);
      
  };

}

#endif