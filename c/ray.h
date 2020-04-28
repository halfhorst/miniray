#include "vector.h"

#ifndef RAY_H
#define RAY_H

typedef struct {
  Vec3 origin;
  Vec3 direction;
} Ray;

Vec3 point_at_parameter(Ray r, float t);

#endif
