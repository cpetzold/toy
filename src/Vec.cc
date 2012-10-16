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

  // Handle<Value> Vec::newInstance(const Arguments& args) {
  //   HandleScope scope;

  //   const unsigned argc = args.Length();
  //   Handle<Value> argv[argc] = {};
  //   for (unsigned i = 0; i < argc; i++) {
  //     argv[i] = args[i];
  //   }

  //   Local<Object> instance = Vec::constructor->NewInstance(argc, argv);
  //   return scope.Close(instance);
  // }

  Persistent<Function> Vec::constructor;

  void Vec::bind(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(Vec::newFunc);
    tpl->SetClassName(String::NewSymbol("Vec"));

    Local<ObjectTemplate> instance = tpl->InstanceTemplate();
    instance->SetInternalFieldCount(1);
    instance->SetAccessor(String::New("x"), Vec::getX, Vec::setX);
    instance->SetAccessor(String::New("y"), Vec::getY, Vec::setY);

    Local<ObjectTemplate> proto = tpl->PrototypeTemplate();
    proto->Set(String::NewSymbol("mult"), FunctionTemplate::New(Vec::mult)->GetFunction());
    proto->Set(String::NewSymbol("multSelf"), FunctionTemplate::New(Vec::multSelf)->GetFunction());
    proto->Set(String::NewSymbol("div"), FunctionTemplate::New(Vec::div)->GetFunction());
    proto->Set(String::NewSymbol("add"), FunctionTemplate::New(Vec::add)->GetFunction());
    proto->Set(String::NewSymbol("addSelf"), FunctionTemplate::New(Vec::addSelf)->GetFunction());

    Vec::constructor = Persistent<Function>::New(tpl->GetFunction());
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

  void Vec::operator=(const Vec &v) {
    this->x = v.x;
    this->y = v.y;
  }

  Vec Vec::operator*(const Vec &v) const {
    return Vec(this->x * v.x, this->y * v.y);
  }
  Vec Vec::operator*(GLfloat scalar) const {
    return Vec(this->x * scalar, this->y * scalar);
  }
  Handle<Value> Vec::mult(const Arguments& args) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(args.This());
    Vec r;

    if (args[0]->IsNumber()) {
      r = *v * args[0]->NumberValue();
    } else if (args[0]->IsObject()) {
      r = *v * *ObjectWrap::Unwrap<Vec>(args[0]->ToObject());
    } else {
      ThrowException(Exception::TypeError(String::New("Argument must either be a number or another Vec")));
      return scope.Close(Undefined());
    }

    const unsigned argc = 2;
    Handle<Value> argv[argc] = { Number::New(r.x), Number::New(r.y) };
    Handle<Value> instance = Vec::constructor->NewInstance(argc, argv);

    return scope.Close(instance);
  }

  void Vec::operator*=(const Vec &v) {
    this->x *= v.x;
    this->y *= v.y;
  }
  void Vec::operator*=(GLfloat scalar) {
    this->x *= scalar;
    this->y *= scalar;
  }
  Handle<Value> Vec::multSelf(const Arguments& args) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(args.This());
    if (args[0]->IsNumber()) {
      v->operator*=(args[0]->NumberValue());
    } else if (args[0]->IsObject()) {
      v->operator*=(*ObjectWrap::Unwrap<Vec>(args[0]->ToObject()));
    }
    return scope.Close(args.This());
  }

  Vec Vec::operator/(GLfloat scalar) const {
    return Vec(this->x / scalar, this->y / scalar);
  }
  Handle<Value> Vec::div(const Arguments& args) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(args.This());
    Vec r;

    if (args[0]->IsNumber()) {
      r = *v / args[0]->NumberValue();
    } else {
      ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
      return scope.Close(Undefined());
    }

    const unsigned argc = 2;
    Handle<Value> argv[argc] = { Number::New(r.x), Number::New(r.y) };
    Handle<Value> instance = Vec::constructor->NewInstance(argc, argv);

    return scope.Close(instance);
  }

  Vec Vec::operator+(const Vec &v) const {
    return Vec(this->x + v.x, this->y + v.y);
  }
  Handle<Value> Vec::add(const Arguments& args) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(args.This());
    Vec r;

    if (args[0]->IsObject()) {
      r = *v + *ObjectWrap::Unwrap<Vec>(args[0]->ToObject());
    } else {
      ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
      return scope.Close(Undefined());
    }

    const unsigned argc = 2;
    Handle<Value> argv[argc] = { Number::New(r.x), Number::New(r.y) };
    Handle<Value> instance = Vec::constructor->NewInstance(argc, argv);

    return scope.Close(instance);
  }

  void Vec::operator+=(const Vec &v) {
    this->x += v.x;
    this->y += v.y;
  }
  Handle<Value> Vec::addSelf(const Arguments& args) {
    HandleScope scope;
    Vec* v = ObjectWrap::Unwrap<Vec>(args.This());
    if (args[0]->IsObject()) {
      *v += *ObjectWrap::Unwrap<Vec>(args[0]->ToObject());
    } else {
      ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
      return scope.Close(Undefined());
    }
    return scope.Close(args.This());
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