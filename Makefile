.KEEP_STATE:
.SUFFIXES: .o .f90 .cpp

F90 = gfortran
CC = g++
Lib =  -lm -lGL -lGLU -lglut -lgfortran
GDB = -g -Wall -Wextra -O3
SRC = ./CPP_2D_3D/main.cpp ./CPP_2D_3D/window.cpp ./CPP_2D_3D/spheres.cpp ./CPP_2D_3D/datastructures.cpp
OBJ = $(OBJDIR)/datastructures.o $(OBJDIR)/spheres.o $(OBJDIR)/main.o $(OBJDIR)/gaussian.o $(OBJDIR)/window.o
SRCDIR = ./CPP_2D_3D
OBJDIR = ./obj


#all: $(OBJDIR)/main.o $(OBJDIR)/window.o $(OBJDIR)/spheres.o $(OBJDIR)/datastructures.o brown

all: $(OBJDIR)/gaussian.o brown

$(OBJDIR)/gaussian.o : $(SRCDIR)/gaussian.f90
	$(F90) -c -o $@ $< $(GDB)

#$(OBJDIR)/main.o : $(SRCDIR)/main.cpp
#	$(CC) -c $(Lib) -o $@ $< $(GDB)


#$(OBJDIR)/window.o : $(SRCDIR)/window.cpp
#	$(CC) -c $(Lib) -o $@ $< $(GDB)

#$(OBJDIR)/spheres.o : $(SRCDIR)/spheres.cpp
#	$(CC) -c $(Lib) -o $@ $< $(GDB)

#$(OBJDIR)/datastructures.o : $(SRCDIR)/datastructures.cpp
#	$(CC) -c $(Lib) -o $@ $< $(GDB)


brown : $(SRC)
	$(CC) -o brown $(SRC) $(OBJDIR)/gaussian.o $(GDB) $(Lib)




clean:
	rm $(OBJDIR)/* brown
