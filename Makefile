.KEEP_STATE:
.SUFFIXES: .o .f90 .cpp

F90 = gfortran
CC = g++
Lib =  -lm -lGL -lGLU -lglut -lgfortran -pthread
GDB =  -pg -Wall -Wextra -O3
SRC = $(SRCDIR)/browniansim.cpp $(SRCDIR)/main.cpp $(SRCDIR)/window.cpp $(SRCDIR)/spheres.cpp $(SRCDIR)/vec.cpp $(SRCDIR)/collisionhandler.cpp
OBJ = $(OBJDIR)/datastructures.o $(OBJDIR)/spheres.o $(OBJDIR)/main.o $(OBJDIR)/gaussian.o $(OBJDIR)/window.o
SRCDIR = ./CPP_2D_3D
OBJDIR = ./obj



all: $(OBJDIR)/gaussian.o brown

$(OBJDIR)/gaussian.o : $(SRCDIR)/gaussian.f90
	$(F90) -c -o $@ $< $(GDB)

brown : $(SRC)
	$(CC) -o brown $(SRC) $(OBJDIR)/gaussian.o $(GDB) $(Lib)




clean:
	rm $(OBJDIR)/* brown
