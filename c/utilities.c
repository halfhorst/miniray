#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "utilities.h"
#include "vector.h"

void print_progress(int curr_ray, int total_ray, int curr_sample, int total_sample) {
  // TODO: handle term resizing
  // TODO: use ncurses to hide the pesky cursor
  int i, bar_width;

  bar_width = 25;

  fprintf(stderr, "\r");
  for (i = 0; i < bar_width + 10; i++) {
    fprintf(stderr, " ");
  }

  // print ray progress
  fprintf(stderr, "\r");
  int curr_ray_scaled = ((float) curr_ray / (float) total_ray) * bar_width;
  for (i = 0; i < bar_width; i++) {
    if (i < curr_ray_scaled) {
      fprintf(stderr, "▉");
    } else{
      fprintf(stderr, "░");
    }
  }
  fprintf(stderr, " (ray %d / %d) ", curr_ray, total_ray);
}

// results in cos^3(phi) ray scattering from normal
Vec3 random_point_in_unit_sphere(void) {
  while (true) {
    Vec3 candidate = random_vector(-1.0, 1.0);
    if (length(candidate) >= 1.0) continue;
    return candidate;
  }
}

// results in cos(phi) ray scattering from normal
Vec3 random_vector_on_unit_sphere(void) {
  float theta = random_float_range(0, 2 * M_PI);
  float y = random_float_range(-1, 1);
  float circle_r = sqrtf(1 - (y * y));
  Vec3 unit_vec = {.x=circle_r*cosf(theta), .z=y, .y=circle_r*sinf(theta)};
  return unit_vec;
}

// uniform scattering from normal. Used to generate bounced ray
// in the correct direction outright instead of a displacement to
// add to the normal
Vec3 random_in_hemisphere(Vec3 normal) {
  Vec3 in_unit_sphere = random_point_in_unit_sphere();
  if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
      return in_unit_sphere;
  else
      return negate(in_unit_sphere);
}

Vec3 random_in_unit_disk() {
  while(true) {
    Vec3 p = make_vector(random_float_range(-1, 1), random_float_range(-1, 1), 0);
    if (squared_length(p) >= 1) continue;
    return p;
  }
}

Vec3 random_vector(float min, float max) {
  Vec3 random = {.x = random_float_range(min, max),
                 .y = random_float_range(min, max),
                 .z = random_float_range(min, max)};

  return random;
}

inline float random_float(void) {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float_range(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_float();
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline float ffmin(float x, float y) {
  return x <= y ? x : y;
}

inline float ffmax(float x, float y) {
  return x >= y ? x : y;
}

inline float degrees_to_radians(float degrees) {
    return degrees * M_PI / 180;
}
