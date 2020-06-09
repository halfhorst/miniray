#include <math.h>

#include "camera.h"
#include "utilities.h"
#include "vector.h"

Camera get_camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov,
                  float aspect_ratio, float aperture, float focus_dist,
                  float minimum_distance, float maximum_distance) {
  // Generate an orthonormal basis for the camera
  Vec3 origin = lookfrom;
  Vec3 w = unit_vector(subtract(lookfrom, lookat));
  Vec3 u = unit_vector(cross(vup, w));
  Vec3 v = cross(w, u);

  // generate vectors pointing to the corners of our canvas
  float theta = degrees_to_radians(vfov);
  float half_height = tanf(theta / 2);
  float half_width = aspect_ratio * half_height;

  Vec3 half_width_vec = multiplyf(u, half_width * focus_dist);
  Vec3 half_height_vec = multiplyf(v, half_height * focus_dist);

  Vec3 lower_left_corner = subtract(subtract(subtract(origin, half_width_vec),
                                             half_height_vec),
                                    multiplyf(w, focus_dist));
  Vec3 horizontal = multiplyf(u, 2 * half_width * focus_dist);
  Vec3 vertical = multiplyf(v, 2 * half_height * focus_dist);

  Camera c = {.lower_left_corner = lower_left_corner,
              .horizontal = horizontal,
              .vertical = vertical,
              .origin = origin,
              .u = u,
              .w = w,
              .v = v,
              .lens_radius = aperture / 2,
              .minimum_distance = minimum_distance,
              .maximum_distance = maximum_distance};
  return c;
}

Ray get_ray(Camera *c, float s, float t) {
  Vec3 rd = multiplyf(random_in_unit_disk(), c->lens_radius);
  Vec3 offset = add(multiplyf(c->u, rd.x), multiplyf(c->v, rd.y));

  Vec3 direction = subtract(subtract(add(c->lower_left_corner,
                                         add(multiplyf(c->horizontal, s),
                                             multiplyf(c->vertical, t))),
                                     c->origin),
                            offset);
  Ray r = {.origin = add(c->origin, offset), .direction = direction};
  return r;
}
