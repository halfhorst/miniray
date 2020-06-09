CFLAGS = -std=c99 -g -Wall -Werror -pedantic
LDFLAGS = -lm
TARGET = raytracer
DEFAULT_DIMS = 512 256

HEADERS = camera.h hittable.h materials.h scene.h utilities.h vector.h

all: $(TARGET)

$(TARGET): camera.o hittable.o main.o materials.o scene.o utilities.o vector.o $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDFLAGS)

# Examples

gradient: $(TARGET)
	./$(TARGET) $(DEFAULT_DIMS) gradient > gradient.ppm

spheres: $(TARGET)
	./$(TARGET) $(DEFAULT_DIMS) spheres > sphere.ppm

clean:
	$(RM) $(TARGET) *.o *.ppm

