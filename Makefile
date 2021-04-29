.KEEP_STATE:
.SUFFIXES: .o .cpp

F90 = gfortran
CC = g++
Lib =  -lm -lGL -lGLU -lglut -pthread
GDB =  -pg -O3
SRC = $(SRCDIR)/browniansim.cpp $(SRCDIR)/main.cpp $(SRCDIR)/window.cpp $(SRCDIR)/spheres.cpp $(SRCDIR)/vec.cpp $(SRCDIR)/collisionhandler.cpp
SRCDIR = ./src



brown : $(SRC)
	$(CC) -o brown $(SRC) $(GDB) $(Lib)




clean:
	rm brown
