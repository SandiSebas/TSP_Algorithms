#ifndef _HILL_CLIMBING
#define _HILL_CLIMBING
#include <vector>
#include <numeric>
#include "../DistanceMatrix/DistanceMatrix.hpp"

class HillClimbing {
    private:
        std::vector<int> bestTour;
        int minCost;

        std::vector<std::vector<int>> getNeighbor(std::vector<int>& currentTour) const;

    public:
        HillClimbing();

        void solve(int iterMax, DistanceMatrix& distMatrix);
        void print() const;
};

#endif