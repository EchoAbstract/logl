#ifndef VEC4_HH
#define VEC4_HH

#include "Types.hh"
#include "math/Vec2.hh"
#include "math/Vec3.hh"

namespace math {
struct Vec4 {
  Float x;
  Float y;
  Float z;
  Float w;

  Vec4();
  Vec4(const Vec2 &vec);
  Vec4(const Vec3 &vec);
  Vec4(const glm::vec4 &vec);
  Vec4(Float x, Float y, Float z, Float w);
  Vec4(std::initializer_list<Float> l);

  explicit Vec4(Float v);

  Vec4 &operator=(Float v);
  Vec4 &operator=(std::initializer_list<Float> l);
  Vec4 &operator=(const Vec2 &v);
  Vec4 &operator=(const Vec3 &v);
  Vec4 &operator=(const glm::vec4 &g);

  Vec3 xyz() const;

  // GLM convenience functions
  glm::vec3 gxyz() const;
  glm::vec4 gxyzw() const;
};
}

#endif
