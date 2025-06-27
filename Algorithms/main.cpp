#include "DistanceMatrix/DistanceMatrix.hpp"
#include "HillClimbing/HillClimbing.hpp"
#include "SimulatedAnnealing/SimulatedAnnealing.hpp"
#include "GeneticAlgorithm/GeneticAlgorithm.hpp"
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    DistanceMatrix distMatrix = DistanceMatrix();
    
    HillClimbing algorithmHC = HillClimbing();
    SimulatedAnnealing algorithmSA = SimulatedAnnealing();

    GeneticAlgorithm algorithmGA = GeneticAlgorithm();
    for(int i = 0; i < 15; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        algorithmGA.solve(distMatrix);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << duration.count() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        start = std::chrono::high_resolution_clock::now();
        algorithmSA.solve(1000.0, 0.995, distMatrix);
        stop = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << duration.count() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
      
        start = std::chrono::high_resolution_clock::now();
        algorithmHC.solve(distMatrix);
        stop = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << duration.count() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }  
    
    return 0;
}