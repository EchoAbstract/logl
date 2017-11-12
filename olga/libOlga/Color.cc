#include "Color.hh"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

Color::Color() : baseColor_(glm::vec4(0.0, 0.0, 0.0, 1.0)) {}
Color::Color(glm::vec3 color) : baseColor_(glm::vec4(color, 1.0)) {}
Color::Color(glm::vec4 color) : baseColor_(color) {}
Color::Color(Float r, Float g, Float b) : baseColor_(glm::vec4(r, g, b, 1.0)) {}
Color::Color(Float r, Float g, Float b, Float a)
    : baseColor_(glm::vec4(r, g, b, a)) {}

glm::vec3 Color::rgb() const { return glm::vec3(baseColor_); }
glm::vec4 Color::rgba() const { return baseColor_; }

Float Color::r() const { return baseColor_.r; }
Float Color::g() const { return baseColor_.g; }
Float Color::b() const { return baseColor_.b; }
Float Color::a() const { return baseColor_.a; }

void Color::setRed(Float r) { baseColor_.r = r; }
void Color::setGreen(Float g) { baseColor_.g = g; }
void Color::setBlue(Float b) { baseColor_.b = b; }
void Color::setAlpha(Float a) { baseColor_.a = a; }

void Color::setValue(glm::vec3 color) { baseColor_ = glm::vec4(color, 1.0); }
void Color::setValue(glm::vec4 color) { baseColor_ = color; }
void Color::setValue(Float r, Float g, Float b) {
  baseColor_ = glm::vec4(r, g, b, 1.0);
}
void Color::setValue(Float r, Float g, Float b, Float a) {
  baseColor_ = glm::vec4(r, g, b, a);
}
