GRID_DIM = -DGRID_DIM=10000

COMPILER = g++

FLAGS = -std=c++0x -O2 -Wall -Wextra -Wpedantic -fopenmp

OS := $(shell uname)
ifeq ($(OS),Darwin)
	COMPILER = g++-8
endif

ifdef SYSTEMROOT
	RM = del /Q
	RD = rmdir /Q
else
	RM = rm -f
	RD = rm -rf
endif

default: all

all: clean rectangles.o functions.o
	mkdir build
	$(COMPILER) $(FLAGS) rectangles.o functions.o -o build/rectangles

rectangles.o:
	$(COMPILER) -c $(FLAGS) $(GRID_DIM) rectangles.cpp -o rectangles.o

functions.o: 
	$(COMPILER) -c $(FLAGS) functions.cpp -o functions.o

clean:
	$(RM) *.o rectangles all
	$(RD) build