COMPILER = mpicxx
RUNNER = mpirun

FLAGS = -std=c++0x -O2 -Wall -Wextra -Wpedantic -fopenmp

ifdef SYSTEMROOT
	RM = del /Q
	RD = rmdir /Q
else
	RM = rm -f
	RD = rm -rf
endif

default: all

all: clean main.o rectangles.o functions.o
	mkdir build
	$(COMPILER) $(FLAGS) main.o rectangles.o functions.o -o build/main

main.o:
	$(COMPILER) -c $(FLAGS) main.cpp -o main.o

rectangles.o:
	$(COMPILER) -c $(FLAGS) rectangles.cpp -o rectangles.o

functions.o: 
	$(COMPILER) -c $(FLAGS) functions.cpp -o functions.o

clean:
	$(RM) *.o rectangles all
	$(RD) build

run:
	$(RUNNER) -np 2 build/main 
