#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;
    
    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
    // Returns the start node 
    Node* getStartNode(Env env);

    // Returns the goal node
    Node* getGoalNode(Env env);

    // Checks if two nodes are equal and returns 'true' if they're equal
    bool areNodesEqual(Node* node1, Node* node2);

    // Returns 'true' if all elements in the openList are in nodesExplored
    bool allClosed(NodeList* openList);

   /* 
    * Checks if the given node is in nodesExplored and 
    * returns 'true' if it is present in nodesExplored 
    */
    bool inNodesExplored(Node* node);

   /* 
    *  Iterates through the openList and returns the smallest estimated
    *  distance to goal found in the list.
    */
    int getSmallestEstDistance(NodeList* openList, Node* goalNode);

   /* 
    * Checks if the given node is in openList and 
    * returns 'true' if it is present in the openList 
    */    
    bool inOpenList(Node* node, NodeList* openList);

    /* 
    * Updates the openList with all the possible nodes the robot can move to,
    * from the given position 'p' 
    */
    void updateOpenList(Node* p, Env env, NodeList* openList);

    // Returns the index of the given node in nodesExplored
    int getIndex(Node* node);

   /* 
    * Returns a NodeList of the neighbours of a given node, 
    * which the robot has visited
    */
    NodeList* getVisitedNeighbours(Node* node, Env env);

};
#endif //COSC_ASSIGN_ONE_PATHSOLVER