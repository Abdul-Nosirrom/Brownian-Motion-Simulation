CC = g++
Lib = -lm -lGL -lGLU -lglut
GDB = -g -Wall -Wextra 
SRC = ./CPP_2D_3D/main.cpp ./CPP_2D_3D/window.cpp ./CPP_2D_3D/spheres.cpp ./CPP_2D_3D/datastructures.cpp
SRCDIR = ./CPP_2D_3D

./brown: $(SRCDIR)/main.cpp
	$(CC) $(SRC) -o brown $(Lib) $(GDB)
