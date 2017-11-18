#ifndef COLOR_HH
#define COLOR_HH

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <initializer_list>

#include "Types.hh"

// Value type, no hidden members
struct Color {

  Float r;
  Float g;
  Float b;
  Float a;

  // ctors
  Color();
  Color(const glm::vec3 &color);
  Color(const glm::vec4 &color);
  Color(Float r, Float g, Float b);
  Color(Float r, Float g, Float b, Float a);
  Color(std::initializer_list<Float> l);

  explicit Color(Float v);

  Color &operator=(Float v);
  Color &operator=(std::initializer_list<Float> l);
  Color &operator=(const glm::vec3 &g);
  Color &operator=(const glm::vec4 &g);

  // GLM convenience functions
  glm::vec3 rgb() const;
  glm::vec4 rgba() const;
};

#endif
