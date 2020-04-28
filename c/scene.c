

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "hittable.h"
#include "materials.h"
#include "ray.h"
#include "scene.h"
#include "utilities.h"
#include "vector.h"

#define CAMERA_MIN 0.01
#define CAMERA_MAX INFINITY
#define MAX_BOUNCE_DEPTH 50    // Maximum ray bounces to follow
#define AA_SAMPLES 100         // Number of rays to sample within-pixel

void initialize_scene(Vec3 scene[], int width, int height) {
  for (int i=0; i<width*height; i++) {
    Vec3 newVec = { .x=0, .y=0, .z=0 };
    scene[i] = newVec;
  }
}

// The "Hello, World" ray tracer, maintained for posterity
void paint_gradient(Vec3 scene[], int width, int height) {
  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      int index = (i * width) + j;
      Vec3 color = {
        .x=(float) j / (float) (width - 1),
        .y=((float) (height - 1) - (float) i) / (float) (height - 1),
        .z=0.2
      };
      scene[index].x = 255.99*color.x;
      scene[index].y = 255.99*color.y;
      scene[index].z = 255.99*color.z;
    }
  }
}

Vec3 color_ray(Ray r, Hittable *world, int num_hittables, int depth) {
  Vec3 black = {.x = 0, .y = 0, .z = 0};
  if (depth <= 0) {
    return black;
  }

  HitRecord hr;
  int hit = -1;
  // find nearest hittable object
  if (num_hittables > 0) {
    float tmax = CAMERA_MAX;
    for (int k = 0; k < num_hittables; k++) {
      if (world[k].hit(&world[k], r, CAMERA_MIN, tmax, &hr)) {
        hit = k;
        tmax = hr.t;
      }
    }
  }
  if (hit >= 0) {
    Ray scattered;
    Vec3 attenuation;
    if (world[hit].material->scatter(world[hit].material, r, hr, &attenuation, &scattered)) {
      return multiply(color_ray(scattered, world, num_hittables, depth-1), attenuation);
    }
    return black;
  }

  return background_color(r);
}

void paint_scene(Vec3 scene[], int image_width, int image_height, Camera cam, Hittable *hittables, int num_hittables) {
  int i, j, sample;
  float u, v;
  // Camera cam = get_camera(vfov, aspect_ratio);

  // We iterate through i, j such that we end up scanning rows from top
  // to bottom. The camera starts @ lower left so we want v to start ~1
  // to add in the camera's vertical component, initially
  int scene_index = 0;
  for (i = image_height - 1; i >= 0; i--) {
    for (j = 0; j < image_width; j++) {
      if (scene_index % 1000 == 0) {
        print_progress(scene_index, image_height * image_width, 0, AA_SAMPLES);
      }
      Vec3 color = {.x = 0, .y = 0, .z = 0};
      for (sample = 0; sample < AA_SAMPLES; sample++) {
        // jitter the sample to produce AA
        u = ((float) j + random_float()) / (float) image_width;
        v = ((float) i + random_float()) / (float) image_height;
        Ray r = get_ray(&cam, u, v);
        // Sum the anti-aliasing samples together
        color = add(color, color_ray(r, hittables, num_hittables, MAX_BOUNCE_DEPTH));
      }
      // re-scale the summed AA color, gamma correct, and re-scale to 256 colors
      float aa_rescale = 1.0 / AA_SAMPLES;
      scene[scene_index].x = 256.0 * clamp(sqrtf(aa_rescale * color.x), 0.0, 0.999);
      scene[scene_index].y = 256.0 * clamp(sqrtf(aa_rescale * color.y), 0.0, 0.999);
      scene[scene_index].z = 256.0 * clamp(sqrtf(aa_rescale * color.z), 0.0, 0.999);
      scene_index++;
    }
  }
  print_progress(image_height * image_width, image_height * image_width, 0, AA_SAMPLES);
  fprintf(stderr, "\n");
}

Vec3 background_color(Ray r) {
    Vec3 unit_dir = unit_vector(r.direction);
    float t = 0.5*(unit_dir.y + 1.0);
    Vec3 white = {.x=1.0, .y=1.0, .z=1.0};
    Vec3 sky_blue = {.x=0.5, .y=0.7, .z=1.0};

    return add(multiplyf(white, 1.0 - t), multiplyf(sky_blue, t));
}

void print_ppm(Vec3* scene, int width, int height) {
    printf("P3\n%d %d\n255\n", width, height);
    for (int i=0; i<(width * height); i++) {
        if (i % width == 0) {
            printf("\n");
        }
        printf("%d %d %d ", (int) scene[i].x, (int) scene[i].y, (int) scene[i].z);
    }
    printf("\n");
}
