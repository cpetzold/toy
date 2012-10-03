#include "Vec.h"

namespace mg {

  Vec Vec::operator*(GLfloat scalar) const {
    return Vec(this->x * scalar, this->y * scalar);
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