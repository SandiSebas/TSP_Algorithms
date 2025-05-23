#include "SimulatedAnnealing.hpp"

SimulatedAnnealing::SimulatedAnnealing() : minCost(INT_MAX) {
    std::srand(seed);
}

std::vector<int> SimulatedAnnealing::getNeighbor(const std::vector<int>& tour) const {
    std::vector<int> neighbor = tour;
    int i = rand() % neighbor.size();
    int j = rand() % neighbor.size();

    std::swap(neighbor[i], neighbor[j]);
    return neighbor;
}

void SimulatedAnnealing::solve(double temp, double coolingRate, int iterMax, DistanceMatrix& distMatrix) {
    int n = distMatrix.size();
    std::vector<int> currentTour(n);
    std::iota(currentTour.begin(), currentTour.end(), 0);
    int currentCost = distMatrix.tourDistance(currentTour);
    
    minCost = currentCost;
    bestTour = currentTour;

    for(int i = 0; i < iterMax && temp > 1e-8; ++i) {
        std::vector<int> neighbor = getNeighbor(currentTour);
        int neighborCost = distMatrix.tourDistance(neighbor);
        int delta = neighborCost - currentCost;

        if (delta < 0 || std::exp(-delta / temp) > (rand() / (double)RAND_MAX)) {
            currentTour = neighbor;
            currentCost = neighborCost;
        }

        if (currentCost < minCost) {
            bestTour = currentTour;
            minCost = currentCost;
        }

        temp *= coolingRate;
    }
}

void SimulatedAnnealing::print() const {
    std::cout << "Best tour found (cost = " << minCost << "):\n";
    for (int city : bestTour) {
        std::cout << city << " -> ";
    }
    std::cout << bestTour.front() << std::endl;
}