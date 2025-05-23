#ifndef _DISTANCE_MATRIX
#define _DISTANCE_MATRIX
#include "../Node/Node.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>

constexpr int n = 25;
constexpr int seed = 19;

class DistanceMatrix {
    private:

        std::vector<std::vector<int>> distMatrix;
        std::vector<Node> cities;

        void generateCities();
        void computeDistances();

    public:
        DistanceMatrix();
        void print() const;
};

#endif