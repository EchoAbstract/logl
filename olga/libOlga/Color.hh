#ifndef COLOR_HH
#define COLOR_HH

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Types.hh"

// TODO (brian): Forward all the things
class Color {

public:
  Color();
  Color(glm::vec3 color);
  Color(glm::vec4 color);
  Color(Float r, Float g, Float b);
  Color(Float r, Float g, Float b, Float a);

  glm::vec3 rgb() const;
  glm::vec4 rgba() const;

  Float r() const;
  Float g() const;
  Float b() const;
  Float a() const;

  void setRed(Float r);
  void setGreen(Float g);
  void setBlue(Float b);
  void setAlpha(Float a);

  void setValue(glm::vec3 color);
  void setValue(glm::vec4 color);
  void setValue(Float r, Float g, Float b);
  void setValue(Float r, Float g, Float b, Float a);

private:
  glm::vec4 baseColor_;
};

#endif
