#include "vector.h"
#include "ray.h"

Vec3 point_at_parameter(Ray r, float t) {
  return add(r.origin, multiplyf(r.direction, t));
}
