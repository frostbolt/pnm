#include <stdlib.h>
#include <unistd.h>
#include <iostream>

#include "Solution.h"
#include "condition.h"
#include "rectangles.h"

int main(int argc, char *argv[]) {
    size_t N = 100;
    int opt;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                N = atoi(optarg);
                break;
        }
    }

    std::cout << Trapezium::solve(A, B, N).toString();
    std::cout << LeftRectangle::solve(A, B, N).toString();
    std::cout << RightRectangle::solve(A, B, N).toString();
    std::cout << MidRectangle::solve(A, B, N).toString();

    return 0;
}
