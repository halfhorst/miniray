#include "math.h"
#include "stdlib.h"
#include "stdbool.h"

#include "hittable.h"
#include "materials.h"
#include "ray.h"
#include "vector.h"

// TODO: this pattern is kind of confusing, each object potentially has different
// malloc/free considerations
Hittable make_sphere(Vec3 position, float radius, Material *material) {
  // Vec3 sphere_location = {.x = position.x, .y = position.y, .z = z};
  Sphere *s = malloc(sizeof(Sphere));
  s->center = position;
  s->radius = radius;
  // s->material = (Material *) material;
  Hittable h = {.data = s, .hit = &hit_sphere, .material=material};
  return h;
}

void free_sphere(Hittable h) {
  free(h.data);
}

bool hit_sphere(Hittable *this, Ray r, float tmin, float tmax, HitRecord *hr) {
  Sphere *s = (Sphere *) this->data;

  Vec3 oc = subtract(r.origin, s->center);
  float a = dot(r.direction, r.direction);
  float b = 2.0 * dot(oc, r.direction);
  float c = dot(oc, oc) - (s->radius * s->radius);
  float descriminant = (b * b) - (4.0 * a * c);

  if (descriminant > 0) {
    float t = (-b - sqrtf(descriminant)) / (2.0 * a);
    if (tmin < t && t < tmax) {
      hr->t = t;
      hr->p = point_at_parameter(r, t);
      Vec3 outward_normal = unit_vector(subtract(hr->p, s->center));
      hr->front_face = dot(r.direction, outward_normal) < 0;
      hr->normal = hr->front_face ? outward_normal : negate(outward_normal);
      hr->object = this;
      return true;
    }
    t = (-b + sqrtf(descriminant)) / (2.0 * a);
    if (tmin < t && t < tmax) {
      hr->t = t;
      hr->p = point_at_parameter(r, t);
      Vec3 outward_normal = unit_vector(subtract(hr->p, s->center));
      hr->front_face = dot(r.direction, outward_normal) < 0;
      hr->normal = hr->front_face ? outward_normal : negate(outward_normal);
      hr->object = this;
      return true;
    }
  }
  return false;
}
