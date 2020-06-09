CFLAGS = -std=c99 -g -Wall -Werror -pedantic
LDFLAGS = -lm
TARGET = raytracer
DEFAULT_DIMS = 512 256

all: $(TARGET)

$(TARGET): camera.o hittable.o main.o materials.o scene.o utilities.o vector.o
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

camera.o: camera.c camera.h vector.h
	$(CC) $(CFLAGS) -c camera.c

hittable.o: hittable.c hittable.h materials.h vector.h
	$(CC) $(CFLAGS) -c hittable.c

main.o: main.c camera.h hittable.h materials.h scene.h vector.h
	$(CC) $(CFLAGS) -c main.c

materials.o: materials.c materials.h hittable.h utilities.h vector.h
	$(CC) $(CFLAGS) -c materials.c

scene.o: scene.c scene.h camera.h hittable.h materials.h scene.h utilities.h vector.h
	$(CC) $(CFLAGS) -c scene.c

utilities.o: utilities.c utilities.h vector.h
	$(CC) $(CFLAGS) -c utilities.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c


# Examples

gradient: $(TARGET)
	./$(TARGET) $(DEFAULT_DIMS) gradient > gradient.ppm

spheres: $(TARGET)
	./$(TARGET) $(DEFAULT_DIMS) spheres > sphere.ppm

clean:
	$(RM) $(TARGET) *.o *.ppm

