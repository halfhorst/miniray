# miniray

This is a toy path tracer, built while following along with Peter Shirley's
"Ray Tracing in One Weekend" book. That book is first in a three part series
that can be read online [here](https://raytracing.github.io/) (thanks to all
who maintain the code and online versions!).

It is implemented in c99. I may end up doing this all over again in a language
I want to gain some familiarity with so the repository is organized with that
in mind. And, until a scene configuration parser is built altering scenes is
laborious. . .

## Current status

The tracer currently represents all the material in the first book. This means:

* Spherical geometry
* Ideal Lambertian materials - These are "matte" colored objects the reflect
  light diffusely.
* Metal materials - These are objects that reflect light like a mirror. There
  is also an optional `fuzz` factor that jitters reflected light, giving a
  rough appearance.
* Dielectrics - These are objets that both reflect and refract. Refraction is
  done in accordance with Snell's law, bendind light according to the ratio of
  the dielectric constants of the materials at the boundary. Schlick's
  approximation is used to decide if a ray should reflect, generating greater
  reflection at steaper viewing angles.
* A positionable and orientable camera
* Depth-of-focus

## TODO

* A simple scene/camera configuration file parser.
* Multithreading.
* Touch up the progress printer and put it under a verbose flag.
* The next book !
* Implementations in other languages.
