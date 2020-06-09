/*
  Hittables are objects that interact with (get hit by) rays in the ray traced
  world. For this simple ray tracer, they are objects with a known geometry,
  and simple analytical solutions for ray intersection.

  A hittable is primarily concerned with determining if an object is hit or
  not, quickly. A `material` is the substance of the object, and dictates how
  the light actually behaves when it hits it. Each hittable holds a material
  that handles light on a hit.

  These two notions are interrelated but conceptually distinct enough that I
  separated them, and suffer a forward declaration in the process.
*/
#include <stdbool.h>

#include "vector.h"

#ifndef MINIRAY_HITTABLE_H_
#define MINIRAY_HITTABLE_H_

// Hittable and HitRecord refer to each other, as do Material and HitRecord
typedef struct Hittable Hittable;
typedef struct HitRecord HitRecord;
struct Material;  // defined in materials.h

/*
  An object in the ray-traced world. It is made up of a hit function that
  determines if an incident ray intersects the object, arbitrary data that
  constitutes the geometry of the object, and a material that affects the
  scattering of light. The hit function must match the data held, as it will
  use it for the intersection calculation.
*/
struct Hittable {
  void *data;
  bool (*hit)(Hittable *this, Ray r, float tmin, float tmax, HitRecord *hr);
  struct Material *material;
};

/* Sphere geometry data. */
typedef struct {
  Vec3 center;
  float radius;
} Sphere;

/* The data resulting from a ray hitting a geometry.*/
struct HitRecord{
  float t;              // ray parameter of hit
  Vec3 p;               // hit location
  Vec3 normal;          // camera-facing normal at the hit location
  Hittable *object;     // the object that was hit
  bool front_face;      // is the intersection face facing the camera?
};

/* Get a hittable containing spherical geometry. */
Hittable make_sphere(Vec3 position, float radius, struct Material *material);

/* Free a sphere Hittable. */
void free_sphere(Hittable h);

#endif  // MINIRAY_HITTABLE_H_
