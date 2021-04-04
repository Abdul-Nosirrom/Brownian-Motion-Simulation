CC = gcc
Lib = -lm -lGL -lGLU -lglut

app: main.c
	$(CC) main.c -o main $(Lib)
