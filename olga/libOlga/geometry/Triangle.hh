#ifndef TRIANGLE_HH
#define TRIANGLE_HH

#include "Point.hh"

namespace geometry {

struct Triangle {
  Point vertex_[3];

  Triangle(const Point &p0, const Point &p1, const Point &p3)
      : vertex_({p0, p1, p2}) {}

  // TODO (brian): Add some error handling here
  const Point &vertex(size_t i) const { return vertex_[i]; };
};
}

#endif
