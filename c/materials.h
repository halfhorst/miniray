#include <stdbool.h>

#include "hittable.h"
#include "vector.h"
#include "ray.h"

#ifndef MATERIALS_H
#define MATERIALS_H

typedef struct Material Material;

struct Material {
  Vec3 albedo;
  float fuzz;               // for metals
  float refractive_index;   // for dielectrics
  bool (*scatter)(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered);
};

// Factories for producing materials w/ correct scattering functions
Material make_lambertian(Vec3 albedo);
Material make_uniform_diffuse(Vec3 albedo);
Material make_metal(Vec3 albedo, float fuzz);
Material make_dielectric(float refractive_index);

#endif
