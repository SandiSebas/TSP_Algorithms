#include "DistanceMatrix/DistanceMatrix.hpp"
#include "HillClimbing/HillClimbing.hpp"
#include "SimulatedAnnealing/SimulatedAnnealing.hpp"
#include <vector>
#include <iostream>
#include <chrono>

int main() {
    DistanceMatrix distMatrix = DistanceMatrix();
    
    HillClimbing algorithmHC = HillClimbing();
    SimulatedAnnealing algorithmSA = SimulatedAnnealing();

    auto start = std::chrono::high_resolution_clock::now();
    algorithmSA.solve(1000.0, 0.995, 1000, distMatrix);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "SIMULATED ANNEALING" << std::endl;
    std::cout << duration.count() << std::endl;
    algorithmSA.print();

    start = std::chrono::high_resolution_clock::now();
    algorithmHC.solve(distMatrix);
    stop = std::chrono::high_resolution_clock::now();

    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "HILL CLIMBING" << std::endl;
    std::cout << duration.count() << std::endl;
    algorithmHC.print();

    return 0;
}