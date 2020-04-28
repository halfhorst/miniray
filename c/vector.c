#include <math.h>
#include <stdio.h>

#include "vector.h"

Vec3 make_vector(float x, float y, float z) {
  Vec3 vec = {.x = x, .y = y, .z = z};
  return vec;
}

void print_vector(Vec3 v1) {
  printf("{x=%f, y=%f, z=%f}\n", v1.x, v1.y, v1.z);
}

Vec3 negate(Vec3 v1) {
  Vec3 negated = { .x=-v1.x, .y=-v1.y, .z=-v1.z };
  return negated;
}

Vec3 add(Vec3 v1, Vec3 v2) {
  Vec3 sum = { .x=v1.x+v2.x, .y=v1.y+v2.y, .z=v1.z+v2.z };
  return sum;
}

Vec3 subtract(Vec3 v1, Vec3 v2) {
  Vec3 difference = { .x=v1.x-v2.x, .y=v1.y-v2.y, .z=v1.z-v2.z };
  return difference;
}

Vec3 multiply(Vec3 v1, Vec3 v2) {
  Vec3 product = { .x=v1.x*v2.x, .y=v1.y*v2.y, .z=v1.z*v2.z };
  return product;
}

Vec3 multiplyf(Vec3 v1, float f) {
  Vec3 product = { .x=v1.x*f, .y=v1.y*f, .z=v1.z*f };
  return product;
}

Vec3 divide(Vec3 v1, Vec3 v2) {
  Vec3 quotient = { .x=v1.x/v2.x, .y=v1.y/v2.y, .z=v1.z/v2.z  };
  return quotient;
}

Vec3 dividef(Vec3 v1, float f) {
  Vec3 quotient = { .x=v1.x/f, .y=v1.y/f, .z=v1.z/f };
  return quotient;
}

float length(Vec3 v1) {
  float length = sqrtf(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
  return length;
}

float squared_length(Vec3 v1) {
  float length = v1.x*v1.x + v1.y*v1.y + v1.z*v1.z;
  return length;
}

void make_unit_vector(Vec3 *v1) {
  float ell = length(*v1);
  v1->x /= ell;
  v1->y /= ell;
  v1->z /= ell;
}

Vec3 unit_vector(Vec3 v1) {
  float ell = length(v1);
  Vec3 unit = {.x=v1.x / ell, .y=v1.y / ell, .z=v1.z / ell};
  return unit;
}

float dot(Vec3 v1, Vec3 v2) {
  float dot = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
  return dot;
}

Vec3 cross(Vec3 v1, Vec3 v2) {
  Vec3 cross = {
    .x=v1.y*v2.z - v1.z*v2.y,
    .y=-(v1.x*v2.z - v1.z*v2.x),
    .z=v1.x*v2.y - v1.y*v2.x
  };
  return cross;
}
