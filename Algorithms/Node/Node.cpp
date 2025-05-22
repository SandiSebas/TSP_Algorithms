#include "Node.hpp"
#include <iostream>
using namespace std;

Node::Node() {
    x = 0;
    y = 0;
}

Node::Node(int x, int y) {
    this->x = x;
    this->y = y;
}

void Node::Coordinates() {
    cout << "(" << this->x << ", " << this->y << ")" << endl; 
}