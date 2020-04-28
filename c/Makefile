CC = gcc
CFLAGS = -std=c99 -g -Wall -Werror -pedantic
LFLAGS = -lm
TARGET = raytracer
DEFAULT_DIMS = 512 256

# TODO: Add debug target, move default ot -O3
# TODO: Profile target, using gprof

all: $(TARGET)

$(TARGET): camera.o hittable.o main.o materials.o ray.o scene.o utilities.o vector.o
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LFLAGS)

camera.o: camera.c camera.h ray.h vector.h
	$(CC) $(CFLAGS) -c camera.c

hittable.o: hittable.c hittable.h materials.h ray.h vector.h
	$(CC) $(CFLAGS) -c hittable.c

main.o: main.c camera.h hittable.h materials.h scene.h vector.h
	$(CC) $(CFLAGS) -c main.c

materials.o: materials.c materials.h hittable.h utilities.h vector.h ray.h
	$(CC) $(CFLAGS) -c materials.c

ray.o: ray.c ray.h vector.h
	$(CC) $(CFLAGS) -c ray.c

scene.o: scene.c scene.h camera.h hittable.h materials.h ray.h scene.h utilities.h vector.h
	$(CC) $(CFLAGS) -c scene.c

utilities.o: utilities.c utilities.h vector.h
	$(CC) $(CFLAGS) -c utilities.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c


# Examples

gradient: $(TARGET)
	./$(TARGET) $(DEFAULT_DIMS) gradient > gradient.ppm

background: $(TARGET)
	./$(TARGET) $(DEFAULT_DIMS) background > background.ppm

sphere: $(TARGET)
	./$(TARGET) $(DEFAULT_DIMS) sphere > sphere.ppm

clean:
	$(RM) $(TARGET) *.o *.ppm

