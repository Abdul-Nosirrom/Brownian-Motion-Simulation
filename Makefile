CC = gcc
Lib = -lm -lGL -lGLU -lglut

app: main.c
	$(CC) main.c spheres.c -o main $(Lib)
