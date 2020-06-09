#include <stdlib.h>

#include "vector.h"

#ifndef MINIRAY_UTILITIES_H_
#define MINIRAY_UTILITIES_H_

#define M_PI 3.14159265358979323846

/* Print renderer progress to stdout. */
void print_progress(int curr_ray, int total_ray, int curr_sample,
                    int total_sample);

/*
  Sample a point inside a sphere of radius one. This results in cos^3(phi) ray
  scattering from normal.
*/
Vec3 random_point_in_unit_sphere(void);

/*
  Sample a point on the surface of a sphere of radius one. This result in
  cos(phi) ray scattering from normal -- ideal Lambertian
*/
Vec3 random_vector_on_unit_sphere(void);

/*
  Sample a point in the half-sphere of radius one encompassing `normal`. This
  results in uniform scattering from normal.
*/
Vec3 random_in_hemisphere(Vec3 normal);

/* Sample a point inside the unit disk in x and y. */
Vec3 random_in_unit_disk(void);

/* Generate a random vector with components in the range [min, max). */
Vec3 random_vector(float min, float max);

/* Generate a random real in [0,1). */
float random_float(void);

/* Generate a random real in [min,max). */
float random_float_range(float min, float max);

/* Return `x` clamped to the range [min, max]. */
float clamp(float x, float min, float max);

/* Get the smaller of `x` and `y`. */
float ffmin(float x, float y);

/* Get the greater of `x` and `y`. */
float ffmax(float x, float y);

float degrees_to_radians(float degrees);

/* A malloc that crashes if it fails. */
void *crash_malloc(size_t size);

#endif  // MINIRAY_UTILITIES_H_
