#include "hittable.h"
#include "vector.h"
#include "ray.h"

#ifndef SCENE_H
#define SCENE_H

void initialize_scene(Vec3 scene[], int m, int n);
void paint_gradient(Vec3 scene[], int m, int n);
Vec3 color_ray(Ray r, Hittable *world, int num_hittables, int max_depth);
void paint_scene(Vec3 scene[], int m, int n, Camera cam, Hittable *hittables, int num_hittables);
Vec3 background_color(Ray r);
void print_ppm(Vec3 scene[], int m, int n);

#endif
