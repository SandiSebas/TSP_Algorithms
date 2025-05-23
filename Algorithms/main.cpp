#include "DistanceMatrix/DistanceMatrix.hpp"
#include "HillClimbing/HillClimbing.hpp"
#include <vector>
#include <iostream>
#include <chrono>

int main() {
    DistanceMatrix distMatrix = DistanceMatrix();
    
    HillClimbing algorithm = HillClimbing();

    auto start = std::chrono::high_resolution_clock::now();
    algorithm.solve(10000, distMatrix);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::seconds>(stop - start);
    std::cout << duration.count() << std::endl;

    algorithm.print();
    return 0;
}