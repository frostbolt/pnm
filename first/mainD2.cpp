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

    std::cout << "{\"Trapezium\": { \"result:\" " << D2::Trapezium::solve(A1, B1, C1, D1, N)  << ", \"err\": " << D2::Trapezium::R(A1, B1, C1, D1, N) << "}," << std::endl;
    std::cout << "\"LeftRectangle\": { \"result:\" " << D2::LeftRectangle::solve(A1, B1, C1, D1, N)  << ", \"err\": " << D2::LeftRectangle::R(A1, B1, C1, D1, N) << "}," << std::endl;
    std::cout << "\"RightRectangle\": { \"result:\" " << D2::RightRectangle::solve(A1, B1, C1, D1, N)  << ", \"err\": " << D2::RightRectangle::R(A1, B1, C1, D1, N) << "}," << std::endl;
    std::cout << "\"MidRectangle\": { \"result:\" " << D2::MidRectangle::solve(A1, B1, C1, D1, N)  << ", \"err\": " << D2::MidRectangle::R(A1, B1, C1, D1, N) << "}," << std::endl;
    std::cout << "\"Simpson\": { \"result:\" " << D2::Simpson::solve(A1, B1, C1, D1, N) << ", \"err\": " << D2::Simpson::R(A1, B1, C1, D1, N) << "}," << std::endl;
    std::cout << "\"ThreeEights\": { \"result:\" " << D2::ThreeEights::solve(A1, B1, C1, D1, N)  << ", \"err\": " << D2::ThreeEights::R(A1, B1, C1, D1, N) << "}}" << std::endl;

    return 0;
}
