/*
  Materials (in this simple renderer) dictate how light scatters from a point.
  They are associated with objects and reproduce effects like diffuse
  specularity (matte colors), shiny and fuzzy reflection like you see in
  metals, and light bending from Snell's law, such as the way glass or water
  bends what you see.
*/
#include <stdbool.h>

#include "hittable.h"
#include "vector.h"

#ifndef MINIRAY_MATERIALS_H_
#define MINIRAY_MATERIALS_H_

typedef struct Material Material;

/*
  Materials define a scatter funtion that uses the data in a hit record to
  generate a scattered ray and return it in `scattered`.
*/
struct Material {
  Vec3 albedo;              // inherent color
  float fuzz;               // for metals
  float refractive_index;   // for dielectrics
  bool (*scatter)(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation,
                  Ray *scattered);
};

// Factories for producing materials with correct scattering functions

/*
  An unrealistic material that colors scattered rays based on the surface
  normal.
*/
Material make_normal(void);

/*
  A material producing a "perfectly diffuse" matte color. Lambertian
  reflectance is an idealized model of the reflectance of light by bumpy
  surfaces that diffuse light. The diffuse rays follow a cosine law - sampled
  reflected rays fall off with the cosine of the angle between the reflected
  ray and the normal.

  `albedo` is the color of the material, specified as an RGB vector.
*/
Material make_lambertian(Vec3 albedo);

/*
  Same as the Lambertian material except it samples rays uniformly around the
  normal rather than falling off with the cosine.
*/
Material make_uniform_diffuse(Vec3 albedo);

/*
  A material that reflects light at the incident angle, as a shiny metal.
  `fuzz` is added to the reflected ray, distorting it. This produces a rough
  metal surface effect.
*/
Material make_metal(Vec3 albedo, float fuzz);

/*
  Dielectrics reflect some fraction of light at the incident angle (like a
  metal) and refract light (let it pass, bending it). The bending of light is
  dictated by Snell's law and the refractive index. Proportion reflected uses
  Schlick's approximation for the Fresnel factor.

  The actual bending effect is a result of the ratio of the refractive indices
  of the materials on either side of the refractive boundary. This function
  assumes air as the other material.
*/
Material make_dielectric(float refractive_index);

#endif  // MINIRAY_MATERIALS_H_
