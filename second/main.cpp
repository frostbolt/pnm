#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <chrono>
#include <mpi.h>

#include "Solution.h"
#include "condition.h"
#include "rectangles.h"

typedef Solution(*function)(double, double, size_t);

#ifndef N
#define N 1000
#endif

Solution methodTester(function solve, int size, int rank) {
    auto startTime = std::chrono::steady_clock::now();
    double result;
    int steps;

    if (rank == 0) {
        std::cout << "Size: " << size << std::endl;
    }

    double divisionSize      = (B - A) / size,
           divisionStart     = A + divisionSize * (rank + 0),
           divisionEnd       = A + divisionSize * (rank + 1);

    Solution divisionSolution  = solve(divisionStart, divisionEnd, N);

    MPI_Reduce(&divisionSolution.s_area, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&divisionSolution.s_steps, &steps, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        std::cout << result << std::endl;
    }

    auto mulTime = std::chrono::steady_clock::now();
    auto runtimeDuration = std::chrono::duration_cast<std::chrono::duration<double>>(mulTime - startTime);
    return Solution(0, result, steps, divisionSolution.error(), runtimeDuration.count());
}


int main(int argc, char *argv[]) {
    int rank, size;

    // init. if err => kill the proccess safely
    int rc = MPI_Init(&argc, &argv);

    if (rc) {
        MPI_Abort(MPI_COMM_WORLD, rc);
    }

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::cout << "Trapezium:"<< std::endl << methodTester(&Trapezium::solve, size, rank).toStringPretty() << std::endl;
    std::cout << "LeftRectangle:"<< std::endl << methodTester(&LeftRectangle::solve, size, rank).toStringPretty() << std::endl;
    std::cout << "RightRectangle:"<< std::endl << methodTester(&RightRectangle::solve, size, rank).toStringPretty() << std::endl;
    std::cout << "MidRectangle:"<< std::endl << methodTester(&MidRectangle::solve, size, rank).toStringPretty() << std::endl;
    std::cout << "Simpson:"<< std::endl << methodTester(&Simpson::solve, size, rank).toStringPretty() << std::endl;
    std::cout << "ThreeEights:"<< std::endl << methodTester(&ThreeEights::solve, size, rank).toStringPretty() << std::endl;


    MPI_Finalize();


    // std::cout << "LeftRectangle:"<< std::endl << LeftRectangle::solve(A, B, N).toStringPretty() << std::endl;
    // std::cout << "RightRectangle:"<< std::endl << RightRectangle::solve(A, B, N).toStringPretty() << std::endl;
    // std::cout << "MidRectangle:"<< std::endl << MidRectangle::solve(A, B, N).toStringPretty() << std::endl;
    // std::cout << "Simpson:"<< std::endl << Simpson::solve(A, B, N).toStringPretty() << std::endl;
    // std::cout << "ThreeEights:"<< std::endl << ThreeEights::solve(A, B, N).toStringPretty() << std::endl;



    return 0;
}
