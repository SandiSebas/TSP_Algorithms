#ifndef _GENETIC_ALGORITHM
#define _GENETIC_ALGORITHM

#include "../DistanceMatrix/DistanceMatrix.hpp"
#include <vector>

class GeneticAlgorithm {
    private:
        int populationSize;
        int generations;
        double mutations;
        double crossovers;
        std::vector<int> bestTour;
        int minCost;

        std::vector<std::vector<int>> initializePopulation(int n) const;
        std::vector<double> fitnessProb(std::vector<std::vector<int>>& population,
            DistanceMatrix& distMatrix);
        std::vector<int> rouletteWheele(std::vector<std::vector<int>>& population,
            std::vector<double>& fitnessProb);
        std::pair<std::vector<int>, std::vector<int>>crossover(const std::vector<int>& parent1,
            const std::vector<int>& parent2) const;
        void mutate(std::vector<int>& child) const;

    public:
    GeneticAlgorithm(int popSize = 250, int gens = 600, double mutationRate = 0.1, double crossovers = 0.8);
    void solve(DistanceMatrix& distMatrix);
    void print() const;
};

#endif