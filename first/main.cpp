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


    std::cout << "Trapezium:"<< std::endl << Trapezium::solve(A, B, N).toStringPretty() << std::endl;
    std::cout << "LeftRectangle:"<< std::endl << LeftRectangle::solve(A, B, N).toStringPretty() << std::endl;
    std::cout << "RightRectangle:"<< std::endl << RightRectangle::solve(A, B, N).toStringPretty() << std::endl;
    std::cout << "MidRectangle:"<< std::endl << MidRectangle::solve(A, B, N).toStringPretty() << std::endl;
    std::cout << "Simpson:"<< std::endl << Simpson::solve(A, B, N).toStringPretty() << std::endl;
    std::cout << "ThreeEights:"<< std::endl << ThreeEights::solve(A, B, N).toStringPretty() << std::endl;

    return 0;
}
