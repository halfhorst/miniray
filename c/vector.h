#ifndef VEC3_H
#define VEC3_H

typedef struct Vec3 {
  float x;
  float y;
  float z;
} Vec3;

Vec3 make_vector(float x, float y, float z);
void print_vector(Vec3 v1);
Vec3 negate(Vec3 v1);
Vec3 add(Vec3 v1, Vec3 v2);
Vec3 subtract(Vec3 v1, Vec3 v2);
Vec3 multiply(Vec3 v1, Vec3 v2);
Vec3 multiplyf(Vec3 v1, float f);
Vec3 divide(Vec3 v1, Vec3 v2);
Vec3 dividef(Vec3 v1, float f);
float length(Vec3 v1);
float squared_length(Vec3 v1);
void make_unit_vector(Vec3 *v1);
Vec3 unit_vector(Vec3 v1);
float dot(Vec3 v1, Vec3 v2);
Vec3 cross(Vec3 v1, Vec3 v2);

#endif