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
void printEnvStdout(Env env, NodeList* solution);

// TO RUN: ./assign1 < tests/test_name.env > tests/output_name.out
// TO COMPILE: g++ -Wall -Werror -std=c++14 -O -o find main.cpp Node.cpp NodeList.cpp PathSolver.cpp
int main(int argc, char** argv){
    
    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

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

    // std::cout << "\nMAZE TO BE SOLVED:\n\n";
    // for (int r = 0; r < ENV_DIM; ++r) {
    //     for (int c = 0; c < ENV_DIM; ++c) {
    //         std::cout << env[r][c];
    //     }
    //     if (r != ENV_DIM-1)
    //     {
    //         std::cout << std::endl;
    //     } else {
    //         std::cout << std::endl;
    //         std::cout << std::endl;
    //         std::cout << std::endl;
    //     }
    // }
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


    std::cout << "\n  ______     ___   _____  ____   ____  ________  ______    _  \n";
    std::cout << ".' ____ \\  .'   `.|_   _||_  _| |_  _||_   __  ||_   _ `. | | \n";
    std::cout << "| (___ \\_|/  .-.  \\ | |    \\ \\   / /    | |_ \\_|  | | `. \\| | \n";
    std::cout << " _.____`. | |   | | | |   _ \\ \\ / /     |  _| _   | |  | || | \n";
    std::cout << "| \\____) |\\  `-'  /_| |__/ | \\ ' /     _| |__/ | _| |_.' /|_| \n";
    std::cout << " \\______.' `.___.'|________|  \\_/     |________||______.' (_) \n\n\n";
                                                                
   for (int r = 0; r < ENV_DIM; ++r) {
        for (int c = 0; c < ENV_DIM; ++c) {
            std::cout << env[r][c];
        }
        if (r != ENV_DIM-1)
        {
            std::cout << std::endl;
        } else{
            std::cout << std::endl;
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
}