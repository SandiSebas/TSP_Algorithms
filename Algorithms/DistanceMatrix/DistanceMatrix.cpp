#include "DistanceMatrix.hpp"

void DistanceMatrix::generateCities() {
    for(int i = 0; i < n; ++i) {
        this->cities[i] = Node(std::rand() % (n * 2), std::rand() % (n * 2));
    }
}

void DistanceMatrix::computeDistances() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double dx = this->cities[i].getX() - this->cities[j].getX();
            double dy = this->cities[i].getY() - this->cities[j].getY();
            this->distMatrix[i][j] = static_cast<int>(std::round(std::sqrt(dx * dx + dy * dy)));
        }
    }
}


DistanceMatrix::DistanceMatrix()
    : distMatrix(n, std::vector<int>(n)), cities(n)
{
    std::srand(seed);
    this->generateCities();
    this->computeDistances();
}

void DistanceMatrix::print() const {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << this->distMatrix[i][j] << " ";
            if(distMatrix[i][j] == 0 && i != j) {
                std::cout << "ALERT !!!!" << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }
}