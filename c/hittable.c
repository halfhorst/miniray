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
  float half_b = dot(oc, r.direction);
  float c = squared_length(oc) - (s->radius * s->radius);
  float descriminant = (half_b * half_b) - (a * c);

  if (descriminant > 0) {
    float root = sqrtf(descriminant);
    float t = (-half_b - root) / a;
    if (tmin < t && t < tmax) {
      hr->t = t;
      hr->p = point_at_parameter(r, t);
      Vec3 outward_normal = dividef(subtract(hr->p, s->center), s->radius);
      set_face_normal(hr, r, outward_normal);
      hr->object = this;
      return true;
    }
    t = (-half_b + root) / a;
    if (tmin < t && t < tmax) {
      hr->t = t;
      hr->p = point_at_parameter(r, t);
      Vec3 outward_normal = dividef(subtract(hr->p, s->center), s->radius);
      set_face_normal(hr, r, outward_normal);
      hr->object = this;
      return true;
    }
  }
  return false;
}

void set_face_normal(HitRecord *hr, Ray r, Vec3 outward_normal) {
  hr->front_face = dot(r.direction, outward_normal) < 0;
  hr->normal = hr->front_face ? outward_normal : negate(outward_normal);
}
