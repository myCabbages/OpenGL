
OS := $(shell uname -s)
OBJS = modelViewer.o modelViewer

ifeq ($(OS), Linux)
  FLAGS = -I/usr/include -L/usr/lib -L/usr/lib/nvidia-340 -lglut -lGLEW -lGL -lGLU -lX11 -Wno-write-strings
endif

ifeq ($(OS), Darwin)
  FLAGS = -framework Cocoa -framework OpenGL -framework GLUT -I/opt/X11/include -L/opt/X11/lib -lGLEW -lGLUT -Wno-write-strings
endif

%: %.cpp
	g++ $*.cpp -o $* $(FLAGS)

clean:
	rm -f core $(OBJS)

