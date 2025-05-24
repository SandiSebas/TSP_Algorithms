#ifndef _SIMULATED_ANNEALING
#define _SIMULATED_ANNEALING
#include <vector>
#include <numeric>
#include <random>
#include <cmath>
#include "../DistanceMatrix/DistanceMatrix.hpp"

class SimulatedAnnealing {
    private:
        std::vector<int> bestTour;
        int minCost;
        std::vector<int> getNeighbor(const std::vector<int>& currentTour) const;

    public:
        SimulatedAnnealing();
        void solve(double temp, double coolingRate, int L, DistanceMatrix& distMatrix);
        void print() const;
};

#endif