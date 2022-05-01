#include "PathSolver.h"
#include <iostream>
#include <algorithm> 
#include <iterator>


PathSolver::PathSolver()
{
    nodesExplored = new NodeList();    
}

PathSolver::~PathSolver()
{
    delete nodesExplored;
    nodesExplored = nullptr;    
}

void PathSolver::forwardSearch(Env env){

    Node* startNode = new Node(*getStartNode(env));
    Node* goalNode = new Node(*getGoalNode(env));

    NodeList* openList = new NodeList();
    openList->addElement(startNode);

    // Node which indicates the current position of the robot
    Node* p = new Node( startNode->getRow(), startNode->getCol(), 
    startNode->getDistanceTraveled());
    
    while (!areNodesEqual(p, goalNode) && !allClosed(openList)) {
        
        for (int i = 0; i < openList->getLength(); ++i) {
            
           /*
            * Checking if the node has already been explored, 
            * and if it has the smallest estimated distance to goal, 
            * and also if is the goal node.
            */
            if (!inNodesExplored(openList->getNode(i)) && 
                openList->getNode(i)->getEstimatedDist2Goal(goalNode) == 
                getSmallestEstDistance(openList, goalNode) && 
                !areNodesEqual(p, goalNode))
            {
                p = new Node( openList->getNode(i)->getRow(), 
                openList->getNode(i)->getCol(), 
                openList->getNode(i)->getDistanceTraveled());
                
                nodesExplored->addElement(p);
                updateOpenList(p, env, openList);
                 
            }
            
        }
    }
    
    delete startNode;
    startNode = nullptr;
    delete goalNode;
    goalNode = nullptr;
    delete openList;
    openList = nullptr;
    delete p;
    p = nullptr;     
}

NodeList* PathSolver::getNodesExplored(){

    NodeList* nodesExploredCopy = new NodeList(*this->nodesExplored);
    return nodesExploredCopy; 

    delete nodesExploredCopy;
    nodesExploredCopy = nullptr;
}

NodeList* PathSolver::getPath(Env env){

    int length = nodesExplored->getLength();

    // Indicates the node we are currently at, while iterating
    Node* p = new Node(nodesExplored->getNode(length-1)->getRow(),
    nodesExplored->getNode(length-1)->getCol(),
    nodesExplored->getNode(length-1)->getDistanceTraveled());

    // Indicates the path of the robot in reverse
    NodeList* reversePath = new NodeList();
    reversePath->addElement(p);
 
    // A NodeList to store all the neighbours of p that the robot has visited
    NodeList* neighbours = nullptr;

    while (!areNodesEqual(p, nodesExplored->getNode(0))) {
        
        neighbours = new NodeList(*this->getVisitedNeighbours(p,env));
        for (int i = 0; i < neighbours->getLength(); ++i) {

            if (neighbours->getNode(i)->getDistanceTraveled() ==
            p->getDistanceTraveled() - 1)
            {
                p = new Node(neighbours->getNode(i)->getRow(),
                neighbours->getNode(i)->getCol(),
                neighbours->getNode(i)->getDistanceTraveled());
                reversePath->addElement(p);    
            }
        }
    }

    // The NodeList which will have the final path of the robot from S to G
    NodeList* finalPath = new NodeList();
    int index = reversePath->getLength() - 1;
    for (int i = 0; i < reversePath->getLength(); ++i) {
        finalPath->addElement(reversePath->getNode(index));
        index = index - 1;
    }

    // A deep copy of the final path of the robot from S to G
    NodeList* finalPathCopy = new NodeList(*finalPath);
    return finalPathCopy;

    delete p;
    p = nullptr;
    delete reversePath;
    reversePath = nullptr;
    delete neighbours;
    neighbours = nullptr;
    delete finalPath;
    finalPath = nullptr;
    delete finalPathCopy;
    finalPathCopy = nullptr;
}

//-----------------------------

Node* PathSolver::getStartNode(Env env){

    Node* startNode = nullptr;
    for (int row = 0; row < ENV_DIM; ++row) {
        for (int col = 0; col < ENV_DIM; ++col) {
            if (env[row][col] == SYMBOL_START)
            {
                startNode = new Node(row, col, 0);
            }
        }
        
    }
    return startNode;

    delete startNode;
    startNode = nullptr;   
}

Node* PathSolver::getGoalNode(Env env){

    Node* goalNode = nullptr;
    for (int row = 0; row < ENV_DIM; ++row) {
        for (int col = 0; col < ENV_DIM; ++col) {
            if (env[row][col] == SYMBOL_GOAL)
            {
                goalNode = new Node(row, col, 0);
            }
        }
        
    }
    return goalNode;

    delete goalNode;
    goalNode = nullptr;
}

bool PathSolver::areNodesEqual(Node* node1, Node* node2){

    bool equal = false;
    if (node1->getRow() == node2->getRow() &&
        node1->getCol() == node2->getCol())
    {
        equal = true;
    }
    return equal;
}

bool PathSolver::allClosed(NodeList* openList){

    bool closed = false;
    int count = 0;
    for (int i = 0; i < openList->getLength(); ++i) {
        if (inNodesExplored(openList->getNode(i)))
        {
            ++count;           
        }
    }
    if (count == openList->getLength())
    {
        closed = true;
    }
    return closed;
}

bool PathSolver::inNodesExplored(Node* node){

    bool exists = false;
    for (int i = 0; i < nodesExplored->getLength(); ++i) {       
        if (areNodesEqual(node, nodesExplored->getNode(i)))
        { 
            exists = true;    
        }
    }
    return exists;
}

int PathSolver::getSmallestEstDistance(NodeList* openList, Node* goalNode){

    // NodeList to store elements in openList, which are not in nodesExplored
    NodeList* nodes = new NodeList();
    for (int i = 0; i < openList->getLength(); ++i) {
        if (!inNodesExplored(openList->getNode(i)))
        {
            nodes->addElement(openList->getNode(i));
        }
    }
    // The minimum Estimated distance which is to be returned
    int minDistance = nodes->getNode(0)->getEstimatedDist2Goal(goalNode);
    if (nodes->getLength()>1)
    {
        for (int i = 1; i < nodes->getLength(); ++i) {
            if (nodes->getNode(i)->getEstimatedDist2Goal(goalNode)<minDistance)
            {
              minDistance = nodes->getNode(i)->getEstimatedDist2Goal(goalNode);
            }
        }
    }
    return minDistance;

    delete nodes;
    nodes = nullptr;
}

bool PathSolver::inOpenList(Node* node, NodeList* openList){

    bool exists = false;
    for (int i = 0; i < openList->getLength(); ++i) {       
        if (areNodesEqual(node, openList->getNode(i)))
        {
            exists = true;    
        }
    }
    return exists;
}

void PathSolver::updateOpenList(Node* p, Env env, NodeList* openList){
    
    // Node which indicates the neighbour of 'p'
    Node* neighbor = nullptr;

   /* 
    * Series of if statements which check if the neighbour is empty or 
    * if it is the goal. If either, the neighbour is added to the openList, 
    * if not already present in the openList.
    */
    if (env[p->getRow()][p->getCol()- 1] == SYMBOL_EMPTY ||
    env[p->getRow()][p->getCol()- 1] == SYMBOL_GOAL)
    {
        neighbor = new Node(p->getRow(), p->getCol()- 1, 
        p-> getDistanceTraveled() +1);

        if (!inOpenList(neighbor, openList))
        {
            openList->addElement(neighbor);
        }
    } 
    if (env[p->getRow()][p->getCol()+ 1] == SYMBOL_EMPTY ||
    env[p->getRow()][p->getCol()+ 1] == SYMBOL_GOAL)
    {
        neighbor = new Node(p->getRow(), p->getCol()+ 1, 
        p-> getDistanceTraveled() +1);

        if (!inOpenList(neighbor, openList))
        {
            openList->addElement(neighbor);
        }
    } 
    if (env[p->getRow()- 1][p->getCol()] == SYMBOL_EMPTY ||
    env[p->getRow()- 1][p->getCol()] == SYMBOL_GOAL)
    {
        neighbor = new Node(p->getRow()-1, p->getCol(), 
        p-> getDistanceTraveled() +1);

        if (!inOpenList(neighbor, openList))
        {
            openList->addElement(neighbor);
        }
    }
    if (env[p->getRow()+ 1][p->getCol()] == SYMBOL_EMPTY ||
    env[p->getRow()+ 1][p->getCol()] == SYMBOL_GOAL)
    {
        neighbor = new Node(p->getRow()+ 1, p->getCol(), 
        p-> getDistanceTraveled() +1);

        if (!inOpenList(neighbor, openList))
        {
            openList->addElement(neighbor);
        }
    }
    delete neighbor;
    neighbor = nullptr;
}

int PathSolver::getIndex(Node* node){

    int index = -1;
    for (int i = 0; i < nodesExplored->getLength(); ++i) {       
        if (areNodesEqual(node, nodesExplored->getNode(i)))
        { 
            index = i;
        }
    }
    return index;
}

NodeList* PathSolver::getVisitedNeighbours(Node* node, Env env){

    // A NodeList to store all the neighbours of the given node
    NodeList* neighbours = new NodeList();
   /*
    * A NodeList to store all the neighbours of the node, 
    * that the robot has already visited 
    */
    NodeList* visitedNeighbours = new NodeList();

    // Defining all the possible neighbours of the given node
    Node* n1 = new Node(node->getRow(), node->getCol()- 1, 0);
    Node* n2 = new Node(node->getRow(), node->getCol()+ 1, 0);
    Node* n3 = new Node(node->getRow()+ 1, node->getCol(), 0);
    Node* n4 = new Node(node->getRow()- 1, node->getCol(), 0);
    neighbours->addElement(n1);
    neighbours->addElement(n2);
    neighbours->addElement(n3);
    neighbours->addElement(n4);

    for (int i = 0; i < neighbours->getLength(); ++i) {
        if (inNodesExplored(neighbours->getNode(i)))
        {             
          int index = getIndex(neighbours->getNode(i));
          int distance = nodesExplored->getNode(index)->getDistanceTraveled();
          neighbours->getNode(i)->setDistanceTraveled(distance);

          visitedNeighbours->addElement(neighbours->getNode(i));
        }
    }
    return visitedNeighbours;

    delete neighbours;
    neighbours = nullptr;
    delete visitedNeighbours;
    visitedNeighbours = nullptr;
    delete n1;
    n1 = nullptr;
    delete n2;
    n2 = nullptr;
    delete n3;
    n3 = nullptr;
    delete n4;
    n4 = nullptr;
}