#include <argp.h>  // TODO: add a verbose flag
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "camera.h"
#include "hittable.h"
#include "materials.h"
#include "scene.h"
#include "vector.h"

// TODO: command line args
// bounce depth, AA samples
// camera position, field of view, aspect ratio
// verbose flag?
// num cpus when multithreaded

int main (int argc, char *argv[]) {

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
  Vec3 *scene = malloc(width * height * sizeof(Vec3));
  initialize_scene(scene, width, height);

  if (strncmp(scene_type, "gradient", 7) == 0) {
    paint_gradient(scene, width, height);
  // } else if (strncmp(scene_type, "background", 10) == 0) {
  //   paint_scene(scene, width, height, NULL, 0);
  } else if (strncmp(scene_type, "sphere", 6) == 0) {

    Material blue_diffuse = make_lambertian(make_vector(0.1, 0.2, 0.5));
    Material green_diffuse = make_lambertian(make_vector(0.8, 0.8, 0.0));
    Material fuzzy_metal = make_metal(make_vector(0.8, 0.6, 0.2), 0.3);
    // Material shiny_metal = make_metal(make_vector(0.5, 0.5, 0.5), 0.0);
    Material dielectric = make_dielectric(1.5);

    int num_objects = 5;
    Hittable world[num_objects];
    world[0] = make_sphere(make_vector(0, 0, -1), 0.5, &blue_diffuse);
    world[1] = make_sphere(make_vector(0, -100.5, -1), 100, &green_diffuse);
    world[2] = make_sphere(make_vector(-1, 0, -1), 0.5, &dielectric);
    world[3] = make_sphere(make_vector(-1, 0, -1), -0.45, &dielectric);
    world[4] = make_sphere(make_vector(1, 0, -1), 0.5, &fuzzy_metal);

    float vfov = 20;
    Vec3 lookfrom = make_vector(3, 3, 2);
    Vec3 lookat = make_vector(0, 0, -1);
    Vec3 vup = make_vector(0, 1, 0);
    float dist_to_focus = length(subtract(lookfrom, lookat));
    float aperture = 2.0;  // bigger aperture, more defocusing effect
    float aspect_ratio = (float) width / (float) height;
    Camera cam = get_camera(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);
    paint_scene(scene, width, height, cam, world, num_objects);
  } else {
    fprintf(stderr, "Unknown scene type: %s. Scene should be one of {gradient}.\n", scene_type);
    return EXIT_FAILURE;
  }

  print_ppm(scene, width, height);
  // TODO: world contains malloc'd mem, memory leak
  free(scene);
}
