#include "DistanceMatrix/DistanceMatrix.hpp"
#include "HillClimbing/HillClimbing.hpp"
#include "SimulatedAnnealing/SimulatedAnnealing.hpp"
#include "GeneticAlgorithm/GeneticAlgorithm.hpp"
#include <vector>
#include <iostream>
#include <chrono>

int main() {
    DistanceMatrix distMatrix = DistanceMatrix();
    
    //HillClimbing algorithmHC = HillClimbing();
    //SimulatedAnnealing algorithmSA = SimulatedAnnealing();
    GeneticAlgorithm algorithmGA = GeneticAlgorithm(400, 1500, 0.07);
    algorithmGA.solve(distMatrix);

    for(int i = 0; i < 30; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        algorithmGA.solve(distMatrix);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Genetic Algorithm " << i << ":" << std::endl;
        std::cout << duration.count() << std::endl;
    }

    /*
    for(int i = 0; i < 30; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        algorithmSA.solve(1000.0, 0.995, 1000, distMatrix);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "SIMULATED ANNEALING " << i << ":" << std::endl;
        std::cout << duration.count() << std::endl;
    }
    */

    /*
    start = std::chrono::high_resolution_clock::now();
    algorithmHC.solve(distMatrix);
    stop = std::chrono::high_resolution_clock::now();

    duration = duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "HILL CLIMBING" << std::endl;
    std::cout << duration.count() << std::endl;
    */

    return 0;
}