#include "Color.hh"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <algorithm>

Color::Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
Color::Color(const glm::vec3 &color)
    : r(color.r), g(color.g), b(color.b), a(1.0) {}
Color::Color(const glm::vec4 &color)
    : r(color.r), g(color.g), b(color.b), a(color.a) {}
Color::Color(Float rr, Float gg, Float bb) : r(rr), g(gg), b(bb), a(1.0f) {}
Color::Color(Float rr, Float gg, Float bb, Float aa)
    : r(rr), g(gg), b(bb), a(aa) {}

Color::Color(std::initializer_list<Float> l) {
  auto first = std::begin(l);
  switch (l.size()) {
  case 1:
    r = *first;
    g = *first;
    b = *first;
    a = *first;
    break;
  case 2:
    r = *first;
    g = *(first + 1);
    b = 0.0f;
    a = 1.0f;
    break;
  case 3:
    r = *first;
    g = *(first + 1);
    b = *(first + 2);
    a = 1.0f;
    break;
  case 4:
    r = *first;
    g = *(first + 1);
    b = *(first + 2);
    a = *(first + 3);
    break;
  default:
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
    break;
  }
}

Color::Color(Float v) : r(v), g(v), b(v), a(v) {}

glm::vec3 Color::rgb() const { return glm::vec3(r, g, b); }
glm::vec4 Color::rgba() const { return glm::vec4(r, g, b, a); }

Color &Color::operator=(Float v) {
  r = g = b = a = v;
  return *this;
}

Color &Color::operator=(std::initializer_list<Float> l) {
  auto first = std::begin(l);
  switch (l.size()) {
  case 1:
    r = *first;
    g = *first;
    b = *first;
    a = *first;
    break;
  case 2:
    r = *first;
    g = *(first + 1);
    b = 0.0f;
    a = 1.0f;
    break;
  case 3:
    r = *first;
    g = *(first + 1);
    b = *(first + 2);
    a = 1.0f;
    break;
  case 4:
    r = *first;
    g = *(first + 1);
    b = *(first + 2);
    a = *(first + 3);
    break;
  default:
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    a = 1.0f;
    break;
  }

  return *this;
}

Color &Color::operator=(const glm::vec3 &gg) {
  r = gg.r;
  g = gg.g;
  b = gg.b;
  a = 1.0f;
  return *this;
}

Color &Color::operator=(const glm::vec4 &gg) {
  r = gg.r;
  g = gg.g;
  b = gg.b;
  a = gg.a;
  return *this;
}
