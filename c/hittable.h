#include "stdbool.h"

#include "vector.h"
#include "ray.h"

#ifndef HITTABLE_H
#define HITTABLE_H

// Defined in materials.h. Hittables and Materials are circular.
// struct Material;
typedef struct Hittable Hittable;
typedef struct HitRecord HitRecord;
struct Material;

// An object in the ray-traced world. It is made up of a hit function that
// determines if an incident ray intersects the object, arbitrary data that
// constitutes the geometry of the object, and a material that affects the
// scattering of light.
struct Hittable {
  void *data;
  bool (*hit)(Hittable *this, Ray r, float tmin, float tmax, HitRecord *hr);
  struct Material *material;
};

typedef struct {
  Vec3 center;
  float radius;
} Sphere;

struct HitRecord{
  float t;              // parameter of hit
  Vec3 p;               // hit location
  Vec3 normal;          // camera-facing normal at the hit location
  Hittable *object;     // the object that was hit
  bool front_face;      // is the intersection face facing the camera?
};

Hittable make_sphere(Vec3 position, float radius, struct Material *material);
bool hit_sphere(Hittable *this, Ray r, float tmin, float tmax, HitRecord *hr);
void set_face_normal(HitRecord *hr, Ray r, Vec3 outward_normal);

#endif
