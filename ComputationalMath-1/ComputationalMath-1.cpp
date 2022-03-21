#include <iostream>
#include <chrono>
#include "ExtendedMatrix.h"
#include "Input.h"
#include "Gaussian Elimination With Partial Pivoting.h"



int main()
{
    std::cout << "Work by G. Dagil, 2nd year ITMO student." << std::endl;
    std::cout << "Gaussian elimination with pivoting." << std::endl;
  
    ExtendedMatrix matrix;
    Input input;
    matrix = input.takeInput();
    matrix.printExtendedMatrix();
    GaussianElimWithPivoting computator = GaussianElimWithPivoting(matrix);
    computator.withDebugPrints = false;

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<double> answer = computator.solveSystem();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    if (answer.empty()) {
        std::cout << "Determinant is zero, therefore no solution can be found." << std::endl;
    }
    else {
        std::cout << "Answer vector: " << std::endl;
        for (int i = 0; i < answer.size(); i++) {
            std::cout << std::fixed;
            std::cout << std::setprecision(3);
            std::cout << i+1 << ": " << answer.at(i) << std::endl;
        }

        std::cout << "Divergence: " << std::endl;
        for (int i = 0; i < computator.divergences.size(); i++) {
            std::cout << i + 1 << ": " << computator.divergences.at(i) << std::endl;
        }
    }

    std::cout << "Computation time: " << duration.count() << " microseconds" << std::endl;

    return 0;
}