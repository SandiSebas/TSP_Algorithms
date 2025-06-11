#include "GeneticAlgorithm.hpp"
#include <numeric>
#include <random>
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(int popSize, int gens, double mutationRate, double crossovers) 
    : populationSize(popSize), generations(gens), mutations(mutationRate), minCost(INT_MAX), crossovers(crossovers) {}

std::vector<std::vector<int>> GeneticAlgorithm::initializePopulation(int n) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<std::vector<int>> population;
    std::uniform_int_distribution<int> distribution(0, n - 1);
    std::vector<int> baseTour(n);
    std::iota(baseTour.begin(), baseTour.end(), 0);

    for(int i = 0; i < populationSize; ++i) {
        std::vector<int> tour = baseTour;
        std::shuffle(tour.begin(), tour.end(), gen);
        population.push_back(tour);
    }

    return population;
}

std::vector<double> GeneticAlgorithm::fitnessProb(std::vector<std::vector<int>>& population,
    DistanceMatrix& distMatrix) 
{
    std::vector<int> distances;
    std::vector<int> fitness;
    for(int i = 0; i < population.size(); ++i) {
        distances.push_back(distMatrix.tourDistance(population[i]));
    }

    int maxPopulationDistance = *max_element(distances.begin(), distances.end());

    for(int i = 0; i < population.size(); ++i) {
        fitness.push_back(maxPopulationDistance - distances[i]);
    }

    int sumPopulationDistances = 0;
    for(int i = 0; i < population.size(); ++i) {
        sumPopulationDistances += fitness[i];
    }

    std::vector<double> fitnessProb;
    for(int i = 0; i < population.size(); ++i) {
        fitnessProb.push_back((double)fitness[i] / (double)sumPopulationDistances);
    }

    return fitnessProb;
}

std::vector<int> GeneticAlgorithm::rouletteWheele(std::vector<std::vector<int>>& population,
    std::vector<double>& fitnessProb)
{
    std::vector<double> cumulativeProbs;
    double currentSum = 0;
    for(int i = 0; i < fitnessProb.size(); ++i) {
        currentSum += fitnessProb[i];
        cumulativeProbs.push_back(currentSum);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    double r = distribution(gen);

    int i = 0;
    while(cumulativeProbs[i] < r) {
        ++i;
    }

    return population[i];
}

std::pair<std::vector<int>, std::vector<int>> GeneticAlgorithm::crossover(const std::vector<int>& parent1,
    const std::vector<int>& parent2) 
const {
    int n = parent1.size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, n - 1);

    std::vector<int> child1(n, -1);
    std::vector<int> child2(n, -1);
    int cut = distribution(gen);

    for(int i = 0; i <= cut; ++i) {
        child1[i] = parent1[i];
        child2[i] = parent2[i];
    }

    int indx = (cut + 1) % n;
    for(int i = 0; i < n; ++i) {
        int city = parent2[(cut + 1 + i) % n];
        if(std::find(child1.begin(), child1.end(), city) == child1.end()) {
            child1[indx] = city;
            indx = (indx + 1) % n;
        }
    }


    indx = (cut + 1) % n;
    for(int i = 0; i < n; ++i) {
        int city = parent1[(cut + 1 + i) % n];
        if(std::find(child2.begin(), child2.end(), city) == child2.end()) {
            child2[indx] = city;
            indx = (indx + 1) % n;
        }
    }

    return {child1, child2};
}

void GeneticAlgorithm::mutate(std::vector<int>& child) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    std::uniform_int_distribution<int> distribution2(0, child.size() - 1);

    if (distribution(gen) < mutations) {
        int i = distribution2(gen);
        int j = distribution2(gen);
        std::swap(child[i], child[j]);
    }
}

void GeneticAlgorithm::solve(DistanceMatrix& distMatrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    int n = distMatrix.size();
    std::uniform_int_distribution<int> indexDis(0, populationSize - 1);

    auto population = initializePopulation(n);
    auto fitness = fitnessProb(population, distMatrix);

    std::vector<std::vector<int>> parentsList;
    for(int i = 0; i < int(crossovers * populationSize); ++i) {
        parentsList.push_back(rouletteWheele(population, fitness));
    }

    std::vector<std::vector<int>> offspringList;
    for(int i = 0; i < parentsList.size(); i += 2) {
        auto offsprings = crossover(parentsList[i], parentsList[i + 1]);
        auto child1 = offsprings.first;
        auto child2 = offsprings.second;

        double prob1 = dist(gen);
        double prob2 = dist(gen);

        if(prob1 > (1.0 - mutations)) {
            mutate(child1);
        }

        if(prob2 > (1.0 - mutations)) {
            mutate(child2);
        }
        offspringList.push_back(child1);
        offspringList.push_back(child2);
    }

    std::vector<std::vector<int>> mixedOffspring = parentsList;
    mixedOffspring.insert(mixedOffspring.end(), offspringList.begin(), offspringList.end());
    fitness = fitnessProb(mixedOffspring, distMatrix);

    std::vector<int> indexes(mixedOffspring.size());
    std::iota(indexes.begin(), indexes.end(), 0);
    std::sort(indexes.begin(), indexes.end(), [&](size_t i, size_t j) {
        return fitness[i] > fitness[j];
    });

    std::vector<std::vector<int>> bestMixedOffspring;
    for (int i = 0; i < populationSize; ++i) {
        bestMixedOffspring.push_back(mixedOffspring[indexes[i]]);
    }

    for(int geni = 0; geni < generations; ++geni) {
        fitness = fitnessProb(bestMixedOffspring, distMatrix);

        parentsList.clear();
        for(int i = 0; i < int(crossovers * populationSize); ++i) {
            parentsList.push_back(rouletteWheele(bestMixedOffspring, fitness));
        }

        offspringList.clear();
        for(int i = 0; i + 1 < parentsList.size(); i += 2) {
            auto offsprings = crossover(parentsList[i], parentsList[i + 1]);
            auto child1 = offsprings.first;
            auto child2 = offsprings.second;

            double prob1 = dist(gen);
            double prob2 = dist(gen);

            if(prob1 > (1.0 - mutations)) {
                mutate(child1);
            }

            if(prob2 > (1.0 - mutations)) {
                mutate(child2);
            }
            offspringList.push_back(child1);
            offspringList.push_back(child2);
        }

        mixedOffspring = parentsList;
        mixedOffspring.insert(mixedOffspring.end(), offspringList.begin(), offspringList.end());
        fitness = fitnessProb(mixedOffspring, distMatrix);

        std::iota(indexes.begin(), indexes.end(), 0);
        std::sort(indexes.begin(), indexes.end(), [&](size_t i, size_t j) {
            return fitness[i] > fitness[j];
        });

        bestMixedOffspring.clear();
        for (int i = 0; i < populationSize; ++i) {
            bestMixedOffspring.push_back(mixedOffspring[indexes[i]]);
        }

        std::shuffle(bestMixedOffspring.begin(), bestMixedOffspring.end(), gen);
    }

    int currentCost = 0;
    for(int i = 0; i < populationSize; ++i) {
        currentCost = distMatrix.tourDistance(bestMixedOffspring[i]);
        if(currentCost < minCost) {
            minCost = currentCost;
            bestTour = bestMixedOffspring[i];
        }
    }
}


void GeneticAlgorithm::print() const {
    std::cout << "Best tour found (cost = " << minCost << "):\n";
    for (int city : bestTour) {
        std::cout << city << " -> ";
    }
    std::cout << bestTour.front() << std::endl;
}