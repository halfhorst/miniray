#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "camera.h"
#include "hittable.h"
#include "materials.h"
#include "scene.h"
#include "vector.h"

#define MAX_BOUNCE_DEPTH 50    // Maximum ray bounces to follow
#define AA_SAMPLES 100         // Number of jittered rays to sample within-pixel
#define CAMERA_MIN 0.01        // Objects closer are ignored
#define CAMERA_MAX INFINITY    // Objects further are ignored



int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "Usage: ./raytracer <m> <n> <scene_type>\n");
    return EXIT_FAILURE;
  }

  int width = atoi(argv[1]);
  int height = atoi(argv[2]);

  if ((width < 0) | (height < 0)) {
    fprintf(stderr, "Invalid dimensions passed.");
    return EXIT_FAILURE;
  }

  char *scene_type = argv[3];

  Scene *scene;
  if (strncmp(scene_type, "gradient", 7) == 0) {
    scene = initialize_scene(width, height, NULL, 0, NULL, MAX_BOUNCE_DEPTH,
                             AA_SAMPLES);
    paint_gradient(scene);
  } else if (strncmp(scene_type, "spheres", 7) == 0) {
    // Setup the world
    Material normal = make_normal();
    // Material blue_diffuse = make_lambertian(make_vector(0.1, 0.2, 0.5));
    Material green_diffuse = make_lambertian(make_vector(0.8, 0.8, 0.0));
    Material fuzzy_metal = make_metal(make_vector(0.8, 0.6, 0.2), 0.3);
    // Material shiny_metal = make_metal(make_vector(0.5, 0.5, 0.5), 0.0);
    Material dielectric = make_dielectric(1.5);

    int num_objects = 5;
    Hittable world[num_objects];
    world[0] = make_sphere(make_vector(0, 0, -1), 0.5, &normal);
    world[1] = make_sphere(make_vector(0, -100.5, -1), 100, &green_diffuse);
    world[2] = make_sphere(make_vector(-1, 0, -1), 0.5, &dielectric);
    world[3] = make_sphere(make_vector(-1, 0, -1), -0.45, &dielectric);
    world[4] = make_sphere(make_vector(1, 0, -1), 0.5, &fuzzy_metal);

    // Setup the camera
    float vfov = 90;
    Vec3 lookfrom = make_vector(0, 0, 0.2);
    Vec3 lookat = make_vector(0, 0, -1);
    Vec3 vup = make_vector(0, 1, 0);
    float dist_to_focus = length(subtract(lookfrom, lookat));
    float aperture = 0.0;  // bigger aperture, more defocusing effect
    float aspect_ratio = (float) width / (float) height;
    Camera camera = get_camera(lookfrom, lookat, vup, vfov, aspect_ratio,
                               aperture, dist_to_focus, CAMERA_MIN,
                               CAMERA_MAX);

    // Setup the scene
    scene = initialize_scene(width, height, world, num_objects, &camera,
                             MAX_BOUNCE_DEPTH, AA_SAMPLES);

    render(scene);
  } else {
    fprintf(stderr, "Unknown scene type: %s. "
                    "Scene should be one of {gradient}.\n", scene_type);
    return EXIT_FAILURE;
  }

  print_ppm(scene);
  free_scene(scene);
}
