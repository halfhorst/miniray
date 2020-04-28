#include <math.h>
#include <stdbool.h>

#include "hittable.h"
#include "materials.h"
#include "utilities.h"
#include "vector.h"
#include "ray.h"

bool lambertian_diffuse_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered);
bool uniform_diffuse_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered);
bool metal_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered);
bool dielectric_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered);
Vec3 reflect(Vec3 v, Vec3 n);
Vec3 refract(Vec3 r_in, Vec3 n, float eta_ratio);
float schlick(float cosine, float refractive_index);

Material make_lambertian(Vec3 albedo) {
  Material lambertian = {.albedo = albedo,
                         .scatter = &lambertian_diffuse_scatter};
  return lambertian;
}

Material make_uniform_diffuse(Vec3 albedo) {
  Material uniform = {.albedo = albedo,
                      .scatter = &uniform_diffuse_scatter};
  return uniform;
}

Material make_metal(Vec3 albedo, float fuzz) {
  Material metal = {.albedo = albedo,
                    .fuzz = fuzz,
                    .scatter = &metal_scatter};
  return metal;
}

Material make_dielectric(float refractive_index) {
  Material dielectric = {.refractive_index = refractive_index,
                         .scatter = &dielectric_scatter};
  return dielectric;
}

// Vec3 simple_material(HitRecord *hr) {
//   Vec3 result = {.x=1.0, .y=0.0, .z=0.0};
//   return result;
// }

// Vec3 normal_map(HitRecord *hr) {
//   // Rescale the normal vector from [-1, 1] to [0, 1]
//   // to be interpreted directly as (R,G,B)
//   Vec3 rescaled = {.x=1+hr->normal.x, .y=1+hr->normal.y, .z=1+hr->normal.z};
//   return multiplyf(rescaled, 0.5);
// }

// no absorption so we return true always
bool lambertian_diffuse_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered) {
  Vec3 albedo = this->albedo;
  Vec3 scatter_direction = add(hr.normal, unit_vector(random_vector_on_unit_sphere()));
  Ray scattered_ray = {.origin = hr.p, .direction = scatter_direction};
  *scattered = scattered_ray;
  *attenuation = albedo;
  return true;
}

// sampling of rays around the normal
bool uniform_diffuse_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered) {
  Vec3 albedo = this->albedo;
  Ray scattered_ray = {.origin = hr.p, .direction = random_in_hemisphere(hr.normal)};
  *scattered = scattered_ray;
  *attenuation = albedo;
  return true;
}

// specular reflection
bool metal_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered) {
  Vec3 albedo = this->albedo;
  Vec3 reflected = reflect(unit_vector(ray_in.direction), hr.normal);
  reflected = add(reflected, multiplyf(random_point_in_unit_sphere(), this->fuzz));
  Ray scattered_ray = {.origin = hr.p, .direction = reflected};
  *scattered = scattered_ray;
  *attenuation = albedo;
  return (dot(scattered_ray.direction, hr.normal) > 0);
}

// TODO: Hollow glass sphere doesn't work
bool dielectric_scatter(Material *this, Ray ray_in, HitRecord hr, Vec3 *attenuation, Ray *scattered) {
  // no absorption by glass
  Vec3 white = {.x = 1.0, .y = 1.0, .z = 1.0};
  *attenuation = white;

  // NOTE: we assume a perfect vaccum (nearly air) as the second medium
  float eta_ratio = (hr.front_face) ? (1.0 / this->refractive_index) : this->refractive_index;

  Vec3 unit_direction = unit_vector(ray_in.direction);
  float cos_theta = ffmin(dot(negate(unit_direction), hr.normal), 1.0);
  float sin_theta = sqrt(1.0 - (cos_theta * cos_theta));

  if ((eta_ratio * sin_theta )> 1.0) {
    Vec3 reflected = reflect(unit_direction, hr.normal);
    Ray scattered_ray = {.origin = hr.p, .direction = reflected};
    *scattered = scattered_ray;
    return true;
  }

  // some reflection at steeper angles
  float reflect_p = schlick(cos_theta, eta_ratio);
  if (random_float() < reflect_p) {
    Vec3 reflected = reflect(unit_direction, hr.normal);
    Ray scattered_ray = {.origin = hr.p, .direction = reflected};
    *scattered = scattered_ray;
    return true;
  }
  Vec3 refracted = refract(unit_direction, hr.normal, eta_ratio);
  Ray scattered_ray = {.origin = hr.p, .direction = refracted};
  *scattered = scattered_ray;
  return true;
}

Vec3 reflect(Vec3 v, Vec3 n) {
  return subtract(v, multiplyf(multiplyf(n, dot(v, n)), 2));
}

Vec3 refract(Vec3 r_in, Vec3 n, float eta_ratio) {
  float cos_theta = dot(negate(r_in), n);
  Vec3 r_out_parallel = multiplyf(add(r_in, multiplyf(n, cos_theta)), eta_ratio);
  Vec3 r_out_perpendicular = multiplyf(n, -1.0 * sqrt(1.0 - squared_length(r_out_parallel)));
  return add(r_out_parallel, r_out_perpendicular);
}

float schlick(float cosine, float refractive_index) {
  float r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
  r0 = r0 * r0;
  return r0 + (1.0 - r0) * pow((1 - cosine), 5.0);
}
