#ifndef _GENETIC_ALGORITHM
#define _GENETIC_ALGORITHM

#include "../DistanceMatrix/DistanceMatrix.hpp"
#include <vector>

class GeneticAlgorithm {
    private:
        int populationSize;
        int generations;
        double mutations;
        std::vector<int> bestTour;
        int minCost;

        std::vector<std::vector<int>> initializePopulation(int n) const;
        std::pair<std::vector<int>, std::vector<int>> selectParent(const std::vector<std::vector<int>>& population,
            DistanceMatrix& distMatrix) const;
        std::vector<int> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) const;
        void mutate(std::vector<int>& tour) const;

    public:
    GeneticAlgorithm(int popSize = 100, int gens = 500, double mutationRate = 0.02);
    void solve(DistanceMatrix& distMatrix);
    void print() const;
};

#endif