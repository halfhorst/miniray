/*
  The Scene holds everything necessary to perform raytracing, and the routines
  here do the actual rendering. A scene is composed of an array of hittable
  objects, an oriented camera, and a grid of pixels that is the render target.
*/
#include "camera.h"
#include "hittable.h"
#include "vector.h"

#ifndef MINIRAY_SCENE_H_
#define MINIRAY_SCENE_H_

typedef struct {
  Camera *camera;
  Vec3 *pixels;
  Hittable *world;
  int world_size;
  int width;
  int height;
  float max_bounce_depth;  // Maximum bounce rays to follow
  float aa_samples;        // Number of jittered rays per pixel
} Scene;

/*
  Allocate a Scene on the heap. Client is responsible for freeing with
  free_scene().
*/
Scene *initialize_scene(int width, int height, Hittable *world, int world_size,
                        Camera *camera, float max_bounce_depth,
                        float aa_samples);

/*
  A raytracing Hello, World. Paints a simple gradient.
*/
void paint_gradient(Scene *scene);

/*
  Returns a color based on the ray `r`. Color is determined by intersedtion
  with an object or a background coloring function.
*/
Vec3 color_ray(Ray r, Hittable *world, int num_hittables, Camera *camera,
               int max_depth);

/*
  The main render loop. It casts rays from the camera through the rendering
  plane, including jitter to produce an antialiased effect.It determines the
  color of each pixel, recording it in the scene.
*/
void render(Scene *scene);

/*
  Returns a color to be used as the background of a scene, when nothing is hit.
*/
Vec3 background_color(Ray r);

/* Print the scene in PPM format to stdout. */
void print_ppm(Scene *scene);

void free_scene(Scene *Scene);

#endif  // MINIRAY_SCENE_H
