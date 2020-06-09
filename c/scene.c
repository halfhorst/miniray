#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "hittable.h"
#include "materials.h"
#include "scene.h"
#include "utilities.h"
#include "vector.h"

// #define CAMERA_MIN 0.01
// #define CAMERA_MAX INFINITY


Scene *initialize_scene(int width, int height, Hittable *world, int world_size,
                        Camera *camera, float max_bounce_depth,
                        float aa_samples) {
  Vec3 *pixels = crash_malloc(width * height * sizeof(Vec3));
  for (int i = 0; i < width * height; i++) {
    Vec3 newVec = { .x = 0, .y = 0, .z = 0 };
    pixels[i] = newVec;
  }

  Scene *scene = crash_malloc(sizeof(Scene));
  scene->pixels = pixels;
  scene->camera = camera;
  scene->width = width;
  scene->height = height;
  scene->world = world;
  scene->world_size = world_size;
  scene->max_bounce_depth = max_bounce_depth;
  scene->aa_samples = aa_samples;
  return scene;
}

void free_scene(Scene *scene) {
  free(scene->pixels);
  free(scene);
}

// TODO:
void prender() {
  // make the appropriate control structures
  // spawn threads and render
  // aggregate the results
}

void paint_gradient(Scene *scene) {
  for (int i = 0; i < scene->height; i++) {
    for (int j = 0; j < scene->width; j++) {
      int index = (i * scene->width) + j;
      Vec3 color = {
        .x = (float) j / (float) (scene->width - 1),
        .y = ((float) (scene->height - 1) - (float) i)
              / (float) (scene->height - 1),
        .z = 0.2
      };
      scene->pixels[index].x = 255.99*color.x;
      scene->pixels[index].y = 255.99*color.y;
      scene->pixels[index].z = 255.99*color.z;
    }
  }
}

Vec3 color_ray(Ray r, Hittable *world, int num_hittables, Camera *camera,
               int depth) {
  Vec3 black = {.x = 0, .y = 0, .z = 0};
  if (depth <= 0) {
    return black;
  }

  HitRecord hr;
  int hit = -1;
  // find nearest hittable object. This is primed for an acceleration
  // structure. Note that the camera works from max distance inward,
  // this is how we end with the nearest intersection.
  if (num_hittables > 0) {
    float tmax = camera->maximum_distance;
    for (int k = 0; k < num_hittables; k++) {
      if (world[k].hit(&world[k], r, camera->minimum_distance, tmax, &hr)) {
        hit = k;
        tmax = hr.t;
      }
    }
  }
  if (hit >= 0) {
    Ray scattered;
    Vec3 attenuation;
    if (world[hit].material->scatter(world[hit].material, r, hr, &attenuation,
                                     &scattered)) {
      return multiply(color_ray(scattered, world, num_hittables, camera,
                                depth-1),
                      attenuation);
    }
    return black;
  }

  return background_color(r);
}

void render(Scene *scene) {
  int i, j, sample;
  float u, v;

  // We iterate through i, j such that we end up scanning rows from top
  // to bottom. The camera starts @ lower left so we want v to start ~1
  // to add in the camera's vertical component at start
  int scene_index = 0;
  for (i = scene->height - 1; i >= 0; i--) {
    for (j = 0; j < scene->width; j++) {
      if (scene_index % 1000 == 0) {
        print_progress(scene_index, scene->height * scene->width, 0,
                       scene->aa_samples);
      }
      Vec3 color = {.x = 0, .y = 0, .z = 0};
      for (sample = 0; sample < scene->aa_samples; sample++) {
        // jitter the sample to produce AA
        u = ((float) j + random_float()) / (float) scene->width;
        v = ((float) i + random_float()) / (float) scene->height;
        Ray r = get_ray(scene->camera, u, v);
        // Sum the anti-aliasing samples together
        color = add(color, color_ray(r, scene->world, scene->world_size,
                                     scene->camera,
                                     scene->max_bounce_depth));
      }
      // re-scale the summed AA color, gamma correct, and re-scale to 256 colors
      float aa_rescale = 1.0 / scene->aa_samples;
      scene->pixels[scene_index].x = 256.0 * clamp(sqrtf(aa_rescale * color.x),
                                                   0.0, 0.999);
      scene->pixels[scene_index].y = 256.0 * clamp(sqrtf(aa_rescale * color.y),
                                                   0.0, 0.999);
      scene->pixels[scene_index].z = 256.0 * clamp(sqrtf(aa_rescale * color.z),
                                                   0.0, 0.999);
      scene_index++;
    }
  }
  print_progress(scene_index, scene->height * scene->width, 0,
                 scene->aa_samples);
  fprintf(stderr, "\n");
}

Vec3 background_color(Ray r) {
    Vec3 unit_dir = unit_vector(r.direction);
    float t = 0.5 * (unit_dir.y + 1.0);
    Vec3 white = {.x = 1.0, .y = 1.0, .z = 1.0};
    Vec3 sky_blue = {.x = 0.5, .y = 0.7, .z = 1.0};
    return add(multiplyf(white, 1.0 - t), multiplyf(sky_blue, t));
}

void print_ppm(Scene *scene) {
    printf("P3\n%d %d\n255\n", scene->width, scene->height);
    for (int i = 0; i < (scene->width * scene->height); i++) {
        if (i % scene->width == 0) {
            printf("\n");
        }
        printf("%d %d %d ", (int) scene->pixels[i].x,
                            (int) scene->pixels[i].y,
                            (int) scene->pixels[i].z);
    }
    printf("\n");
}
