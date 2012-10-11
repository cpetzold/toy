#include "Vec.h"

namespace mg {

  Handle<Value> Vec::newFunc(const Arguments& args) {
    HandleScope scope;
    Vec* v = new Vec();
    v->x = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    v->y = args[1]->IsUndefined() ? 0 : args[1]->NumberValue();
    v->Wrap(args.This());
    return args.This();
  }

  void Vec::init(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(Vec::newFunc);
    tpl->SetClassName(String::NewSymbol("Vec"));

    Local<ObjectTemplate> instance = tpl->InstanceTemplate();
    Local<ObjectTemplate> proto = tpl->PrototypeTemplate();

    instance->SetInternalFieldCount(1);

    instance->SetAccessor(String::New("x"), Vec::getX, Vec::setX);
    instance->SetAccessor(String::New("y"), Vec::getY, Vec::setY);

    proto->Set(String::NewSymbol("print"), FunctionTemplate::New(Vec::print)->GetFunction());

    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
    target->Set(String::NewSymbol("Vec"), constructor);
  }

  Handle<Value> Vec::getX(Local<String> property, const AccessorInfo &info) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(info.This());
    return scope.Close(Number::New(v->x));
  }

  void Vec::setX(Local<String> property, Local<Value> value, const AccessorInfo &info) {
    Vec* v = ObjectWrap::Unwrap<Vec>(info.This());
    v->x = value->NumberValue();
  }

  Handle<Value> Vec::getY(Local<String> property, const AccessorInfo &info) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(info.This());
    return scope.Close(Number::New(v->y));
  }

  void Vec::setY(Local<String> property, Local<Value> value, const AccessorInfo &info) {
    Vec* v = ObjectWrap::Unwrap<Vec>(info.This());
    v->y = value->NumberValue();
  }

  Handle<Value> Vec::print(const Arguments& args) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(args.This());
    cout << v->x << "x" << v->y << endl;
    return args.This();
  }

  void Vec::operator=(const Vec &v) {
    this->x = v.x;
    this->y = v.y;
  }

  Vec Vec::operator*(GLfloat scalar) const {
    return Vec(this->x * scalar, this->y * scalar);
  }
  void Vec::operator*=(const Vec &v) {
    this->x *= v.x;
    this->y *= v.y;
  }
  void Vec::operator*=(GLfloat scalar) {
    this->x *= scalar;
    this->y *= scalar;
  }

  Vec Vec::operator/(GLfloat scalar) const {
    return Vec(this->x / scalar, this->y / scalar);
  }

  Vec Vec::operator+(const Vec &v) const {
    return Vec(this->x + v.x, this->y + v.y);
  }
  void Vec::operator+=(const Vec &v) {
    this->x += v.x;
    this->y += v.y;
  }

  Vec Vec::operator-(const Vec &v) const {
    return Vec(this->x - v.x, this->y - v.y);
  }
  void Vec::operator-=(const Vec &v) {
    this->x -= v.x;
    this->y -= v.y;
  }

  bool Vec::operator<(const Vec &v) {
    return (this->x < v.x && this->y < v.y);
  }
  bool Vec::operator<=(const Vec &v) {
    return (this->x <= v.x && this->y <= v.y);
  }
  bool Vec::operator>(const Vec &v) {
    return (this->x > v.x && this->y > v.y);
  }
  bool Vec::operator>=(const Vec &v) {
    return (this->x >= v.x && this->y >= v.y);
  }

  void Vec::set(GLfloat x, GLfloat y) {
    this->x = x;
    this->y = y;
  }

  void Vec::rotate(GLfloat angle) {
    GLfloat xt = (this->x * cosf(angle)) - (this->y * sinf(angle));
    GLfloat yt = (this->y * cosf(angle)) + (this->x * sinf(angle));
    this->x = xt;
    this->y = yt;
  }

  GLfloat Vec::cross(const Vec &v) const {
    return (this->x * v.y) - (this->y * v.x);
  }

  GLfloat Vec::magnitude() {
    return sqrtf(this->x * this->x + this->y * this->y);
  }

  void Vec::normalize() {
    GLfloat mag = this->magnitude();
    this->x /= mag;
    this->y /= mag;
  }

  GLfloat Vec::dot(const Vec &v) const {
    return (this->x * v.x) + (this->y * v.y);
  }

  Vec Vec::randCenter(const Vec &v) {
    Vec result;
    if (v.x) result.x = (rand() % (int)v.x) - (v.x/2);
    if (v.y) result.y = (rand() % (int)v.y) - (v.y/2);
    return *this + result;
  }

}