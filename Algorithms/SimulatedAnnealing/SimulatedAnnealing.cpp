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

void SimulatedAnnealing::solve(double temp, double coolingRate, DistanceMatrix& distMatrix) {
    int n = distMatrix.size();
    std::vector<int> currentTour(n);
    std::iota(currentTour.begin(), currentTour.end(), 0);

    while(temp > 1e-5) {
        for(int i = 0; i < 200; ++i) {
            auto neighbor = getNeighbor(currentTour);

            int delta = distMatrix.tourDistance(neighbor) - distMatrix.tourDistance(currentTour);

            if(delta < 0 || std::exp(-delta / temp) > (rand() / (double)RAND_MAX)) {
                currentTour = neighbor;
            }
        }

        temp *= coolingRate;
    }
    minCost = distMatrix.tourDistance(currentTour);
    bestTour = currentTour;
}

void SimulatedAnnealing::print() const {
    std::cout << "Best tour found (cost = " << minCost << "):\n";
    for (int city : bestTour) {
        std::cout << city << " -> ";
    }
    std::cout << bestTour.front() << std::endl;
}