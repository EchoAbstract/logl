#include "Vec4.hh"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <algorithm>

Vec4::Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
Vec4::Vec4(const Vec2 &vec) : x(vec.x), y(vec.y), z(0.0), w(0.0) {}
Vec4::Vec4(const Vec3 &vec) : x(vec.x), y(vec.y), z(vec.z), w(0.0) {}
Vec4::Vec4(const glm::vec4 &color)
    : r(color.r), g(color.g), b(color.b), a(color.a) {}
Vec4::Vec4(Float xx, Float yy, Float zz, Float ww)
    : x(xx), y(yy), z(zz), w(ww) {}

Vec4::Vec4(std::initializer_list<Float> l) {
  auto first = std::begin(l);
  switch (l.size()) {
  case 1:
    x = *first;
    y = *first;
    z = *first;
    w = *first;
    break;
  case 2:
    x = *first;
    y = *(first + 1);
    z = 0.0f;
    w = 0.0f;
    break;
  case 3:
    x = *first;
    y = *(first + 1);
    z = *(first + 2);
    w = 0.0f;
    break;
  case 4:
    x = *first;
    y = *(first + 1);
    z = *(first + 2);
    w = *(first + 3);
    break;
  default:
    r = 0.0f;
    g = 0.0f;
    z = 0.0f;
    w = 0.0f;
    break;
  }
}

Vec4::Vec4(Float v) : x(v), y(v), z(v), w(v) {}

Vec3 xyz() const { return Vec3(x, y, z); }
glm::vec3 Vec4::gxyz() const { return glm::vec3(x, y, z); }
glm::vec4 Vec4::gxyzw() const { return glm::vec4(x, y, z, w); }

Vec4 &Vec4::operator=(Float v) {
  x = y = z = w = v;
  return *this;
}

Vec4 &Vec4::operator=(std::initializer_list<Float> l) {
  auto first = std::begin(l);
  switch (l.size()) {
  case 1:
    x = *first;
    y = *first;
    z = *first;
    w = *first;
    break;
  case 2:
    x = *first;
    y = *(first + 1);
    z = 0.0f;
    w = 0.0f;
    break;
  case 3:
    x = *first;
    y = *(first + 1);
    z = *(first + 2);
    w = 0.0f;
    break;
  case 4:
    x = *first;
    y = *(first + 1);
    z = *(first + 2);
    w = *(first + 3);
    break;
  default:
    r = 0.0f;
    g = 0.0f;
    z = 0.0f;
    w = 0.0f;
    break;
  }

  return *this;
}
Vec4 &Vec4::operator=(const Vec2 &v) {
  x = v.x;
  y = v.y;
  z = 0.0;
  w = 0.0;
}
Vec4 &Vec4::operator=(const Vec3 &v) {
  x = v.x;
  y = v.y;
  z = v.z;
  w = 0.0;
}

Vec4 &Vec4::operator=(const glm::vec4 &gg) {
  r = gg.r;
  g = gg.g;
  b = gg.b;
  z = gg.a;
  return *this;
}
