#include "vector.h"
#include "ray.h"

#ifndef CAMERA_H
#define CAMERA_H

typedef struct {
  Vec3 lower_left_corner;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 origin;
  Vec3 u, v, w;
  float lens_radius;
} Camera;

// vfov is specified in degrees
Camera get_camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect_ratio,
                  float aperture, float focus_dist);
Ray get_ray(Camera *c, float u, float v);

#endif
