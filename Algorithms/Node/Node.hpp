#ifndef NODE_HPP
#define NODE_HPP

class Node {
    private:
        int x;
        int y;
    
        public:
            Node();
            Node(int x, int y);
            int getX();
            int getY();
            void Coordinates();
};

#endif