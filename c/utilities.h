#include "vector.h"

#ifndef UTILITIES_H
#define UTILITIES_H

#define M_PI 3.14159265358979323846

void print_progress(int curr_ray, int total_ray, int curr_sample, int total_sample);
Vec3 random_point_in_unit_sphere(void);
Vec3 random_vector_on_unit_sphere(void);
Vec3 random_in_hemisphere(Vec3 normal);
Vec3 random_in_unit_disk();
Vec3 random_vector(float min, float max);
float random_float(void);
float random_float_range(float min, float max);
float clamp(float x, float min, float max);
float ffmin(float x, float y);
float ffmax(float x, float y);
float degrees_to_radians(float degrees);

#endif
