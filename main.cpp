/*
* For milestone 1, I made sure that the tests would have as many patterns
* as possible, and also made sure that they test all the edge cases of 
* the algorithm. Although, it took me a while to figure out what exactly 
* the test cases should be. For milestone 2, other than following the algorithm,
* I tested out different if and while conditions, just to make sure the 
* next position of the robot is being selected carefully. Print statements 
* and short test mazes were used, to observe where the forward search was 
* going wrong. The most challenging part was to figure out which line of code 
* was causing a segmentation fault. Finally fixed the fault after several hours
* of debugging. I also found the implementation of 'deep copy' quite 
* challenging, but referring to the prerecorded videos helped me get a clear 
* understanding. For milestone 3, I used my forward search as a reference to 
* make sure I was checking all the conditions. I also referred to the provided 
* assignment video to get a clear understanding of the algorithms for both 
* milestones 2 and 3. Milestone 3 was not as challenging as the rest, since most
* of it was based on the knowledge we gain while doing milestone 2. Overall, 
* the assignment was quite interesting and needed a very good application 
* of the concepts we have learnt so far.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);

// TO RUN: ./assign1 < tests/test_name.env > tests/output_name.out
int main(int argc, char** argv){
    
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    /*std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;*/

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    
    delete pathSolver;
    pathSolver = nullptr;
    delete exploredPositions;
    exploredPositions = nullptr;
    delete solution;
    solution = nullptr;

}

void readEnvStdin(Env env){
    
    for (int row = 0; row < ENV_DIM; ++row) {
        for (int col = 0; col < ENV_DIM; ++col) { 
            std::cin >> env[row][col];
        }       
    }
}

void printEnvStdout(Env env, NodeList* solution) {

   for (int i = 1; i < solution->getLength()-1; ++i) {

       int row = solution->getNode(i)->getRow();
       int col = solution->getNode(i)->getCol();

       // Checking the positions to print directions accordingly
       if (solution->getNode(i+1)->getRow()== row &&
       solution->getNode(i+1)->getCol()== col -1) 
       {
           env[row][col] = '<';
       }
       if (solution->getNode(i+1)->getRow()== row &&
       solution->getNode(i+1)->getCol()== col +1)
       {
           env[row][col] = '>';
       }
       if (solution->getNode(i+1)->getRow()== row+1 &&
       solution->getNode(i+1)->getCol()== col) 
       {
           env[row][col] = 'v';
       }
       if (solution->getNode(i+1)->getRow()== row-1 &&
       solution->getNode(i+1)->getCol()== col)
       {
           env[row][col] = '^';
       }
    }

   for (int r = 0; r < ENV_DIM; ++r) {
        for (int c = 0; c < ENV_DIM; ++c) {
            std::cout << env[r][c];
        }
        if (r != ENV_DIM-1)
        {
            std::cout << std::endl;
        }
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    //test line  by me ------
    Node* g = new Node(1, 5, 0);
    std::cout << node->getEstimatedDist2Goal(g) << std::endl;
    
    //test line ends ------
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    //test line  by me ------
    
    std::cout << node->getEstimatedDist2Goal(g) << std::endl;
    delete g;
    //test line ends ------
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}