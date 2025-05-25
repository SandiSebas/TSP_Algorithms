#include "GeneticAlgorithm.hpp"
#include <numeric>
#include <random>
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(int popSize, int gens, double mutationRate) 
    : populationSize(popSize), generations(gens), mutations(mutationRate), minCost(INT_MAX) {}

    std::vector<std::vector<int>> GeneticAlgorithm::initializePopulation(int n) const {
    std::vector<std::vector<int>> population;
    std::vector<int> baseTour(n);
    std::iota(baseTour.begin(), baseTour.end(), 0);

    auto rng = std::mt19937(seed);

    for(int i = 0; i < populationSize; ++i) {
        std::vector<int> tour = baseTour;
        std::shuffle(tour.begin(), tour.end(), rng);
        population.push_back(tour);
    }

    return population;
}

std::pair<std::vector<int>, std::vector<int>> GeneticAlgorithm::selectParent(const std::vector<std::vector<int>>& population,
    DistanceMatrix& distMatrix) const 
{
    auto rng = std::mt19937(seed);
    auto pick = [&](int tournamentSize = 5) {
        std::vector<int> best;
        int bestCost = INT_MAX;

        for(int i = 0; i < tournamentSize; ++i) {
            int indx = rng() % population.size();
            int cost = distMatrix.tourDistance(population[indx]);

            if(cost < bestCost) {
                bestCost = cost;
                best = population[indx];
            }
        }
        return best;
    };

    return {pick(), pick()};
}

std::vector<int> GeneticAlgorithm::crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) const {
    int n = parent1.size();

    std::vector<int> child(n, -1);
    int start = rand() % n;
    int end = rand() % n;

    if(start > end) {
        std::swap(start, end);
    }

    for(int i = start; i <= end; ++i) {
        child[i] = parent1[i];
    }

    int indx = (end + 1) % n;
    for(int i = 0; i < n; ++i) {
        int city = parent2[(end + 1 + i) % n];
        if(std::find(child.begin(), child.end(), city) == child.end()) {
            child[indx] = city;
            indx = (indx + 1) % n;
        }
    }

    return child;
}

void GeneticAlgorithm::mutate(std::vector<int>& tour) const {
    if (((double) rand() / RAND_MAX) < mutations) {
        int i = rand() % tour.size();
        int j = rand() % tour.size();
        std::swap(tour[i], tour[j]);
    }
}

void GeneticAlgorithm::solve(DistanceMatrix& distMatrix) {
    int n = distMatrix.size();
    std::vector<std::vector<int>> population = initializePopulation(n);

    for (int gen = 0; gen < generations; ++gen) {
        std::vector<std::vector<int>> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            auto [parent1, parent2] = selectParent(population, distMatrix);
            std::vector<int> child = crossover(parent1, parent2);
            mutate(child);
            newPopulation.push_back(child);

            int cost = distMatrix.tourDistance(child);
            if (cost < minCost) {
                bestTour = child;
                minCost = cost;
            }
        }
        population = newPopulation;
    }
}

void GeneticAlgorithm::print() const {
    std::cout << "Best tour found (cost = " << minCost << "):\n";
    for (int city : bestTour) {
        std::cout << city << " -> ";
    }
    std::cout << bestTour.front() << std::endl;
}