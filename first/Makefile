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

all: clean trapezium.o functions.o
	mkdir build
	$(COMPILER) $(FLAGS) trapezium.o functions.o -o build/trapezium

trapezium.o:
	$(COMPILER) -c $(FLAGS) $(GRID_DIM) trapezium.cpp -o trapezium.o

functions.o: 
	$(COMPILER) -c $(FLAGS) functions.cpp -o functions.o

clean:
	$(RM) *.o trapezium all
	$(RD) build