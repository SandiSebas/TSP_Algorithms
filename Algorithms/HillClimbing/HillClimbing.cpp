#include "HillClimbing.hpp"

HillClimbing::HillClimbing() : minCost(INT_MAX) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

std::vector<std::vector<int>> HillClimbing::getNeighbor(std::vector<int>& currentTour) const {
    std::vector<std::vector<int>> neighbors;
    int i = currentTour.size();
    for (int k = 0; k < n; ++k) {
        int i = rand() % currentTour.size();
        int j = rand() % currentTour.size();

        std::vector<int> neighbor = currentTour;
        std::swap(neighbor[i], neighbor[j]);
        neighbors.push_back(neighbor);
    }
   return neighbors;
}

void HillClimbing::solve(DistanceMatrix& distMatrix) {
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