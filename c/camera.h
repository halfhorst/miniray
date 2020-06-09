/*
  The camera is an orientable origin for rays as well as the definition of the
  extents of a rendering plane. `lower_left_corner` defines a vector pointing
  from the camera's origin to the lower left corner of the rendering plane, and
  horizontal and vertical define the extent of the rendering plane from that
  corner. In this way, lower_left_corner plus a scalar multiplication of
  horizontal and vertical defines a point on the plane.
*/
#include "vector.h"

#ifndef MINIRAY_CAMERA_H_
#define MINIRAY_CAMERA_H_

typedef struct {
  Vec3 lower_left_corner;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 origin;
  Vec3 u, v, w;
  float lens_radius;
  float minimum_distance;    // minimum distance at which to render objects
  float maximum_distance;     // maximum distance at which to render objects
} Camera;

/*
  Get a camera supporting a depth of field. `vfov` is the vertical field of
  view, specified in degrees.
*/
Camera get_camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov,
                  float aspect_ratio, float aperture, float focus_dist,
                  float minimum_distance, float maxium_distance);

/*
  Get a ray from the camera to a point on the rendering plane. `u` and `v`
  should be in [0, 1]. They express fractions of the image vertically and
  horizontally.
*/
Ray get_ray(Camera *c, float u, float v);

#endif  // MINIRAY_CAMERA_H_
