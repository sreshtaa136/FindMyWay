#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
}

Node::~Node(){    

}

Node::Node(Node& other):
    row(other.row),
    col(other.col),
    dist_traveled(other.dist_traveled)
{

}

int Node::getRow(){
    return row;
}

int Node::getCol(){
    return col;
}

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled){
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){

    int manhattan_distance = std::abs(col - goal->getCol()) + 
    std::abs(row - goal->getRow());
    
    int estimated_distance = dist_traveled + manhattan_distance;
    return estimated_distance;
}
    
//--------------------------------                             