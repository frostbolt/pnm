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

    std::cout << "{\"Trapezium\":[" << Trapezium::solve(A, B, N).toString()<< "]," << std::endl;
    std::cout << "\"LeftRectangle\":[" << LeftRectangle::solve(A, B, N).toString()<< "]," << std::endl;
    std::cout << "\"RightRectangle\":[" << RightRectangle::solve(A, B, N).toString()<< "]," << std::endl;
    std::cout << "\"MidRectangle\":[" << MidRectangle::solve(A, B, N).toString()<< "]," << std::endl;
    std::cout << "\"Simpson\":[" << Simpson::solve(A, B, N).toString() << "]," << std::endl;
    std::cout << "\"ThreeEights\":[" << ThreeEights::solve(A, B, N).toString()<< "]}" << std::endl;

    return 0;
}
