#include "HillClimbing.hpp"

HillClimbing::HillClimbing() : minCost(INT_MAX) {
    std::srand(seed);
}

std::vector<std::vector<int>> HillClimbing::getNeighbor(std::vector<int>& currentTour) const {
    std::vector<std::vector<int>> neighbors;
    int i = currentTour.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::vector<int> neighbor = currentTour;
            std::swap(neighbor[i], neighbor[j]);
            neighbors.push_back(neighbor);
        }
    }
    /*
    std::vector<int> neighbor = currentTour;
    int i = rand() % neighbor.size();
    int j = 0;
    do {
        j = rand() % neighbor.size();
    } while(i == j);
    std::swap(neighbor[i], neighbor[j]);
    return neighbor;
    */
   return neighbors;
}

void HillClimbing::solve(int iterMax, DistanceMatrix& distMatrix) {
    int n = distMatrix.size();
    std::vector<int> currentTour(n);
    std::iota(currentTour.begin(), currentTour.end(), 0);
    int currentCost = distMatrix.tourDistance(currentTour);

    while(true) {
        std::vector<std::vector<int>> neighborTour = getNeighbor(currentTour);
        std::vector<int> neighbor;
        int neighborCost = 0;
        int minNeighborCost = INT_MAX;
        for(int j = 0; j < neighborTour.size(); ++j) {
            neighborCost = distMatrix.tourDistance(neighborTour[j]);
            if(neighborCost < minNeighborCost) {
                neighbor = neighborTour[j];
                minNeighborCost = neighborCost;
            }
        }
        

        if(minNeighborCost >= currentCost) {
            break;
        }
        currentTour = neighbor;
        currentCost = minNeighborCost;
    }

    bestTour = currentTour;
    minCost = currentCost; 
}

void HillClimbing::print() const {
    std::cout << "Best tour found (cost = " << minCost << "):\n";
    for (int city : bestTour) {
        std::cout << city << " -> ";
    }
    std::cout << bestTour.front() << std::endl;
}