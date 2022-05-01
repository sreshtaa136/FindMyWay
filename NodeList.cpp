#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{   
   for (int i=0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i) {
       nodes[i] = nullptr;
   }
    length = 0;
}

NodeList::~NodeList()
{
    for(int i=0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i) {
        if (nodes[i] != nullptr) 
        {
            delete nodes[i];
            nodes[i] = nullptr;
        }
    }
}

NodeList::NodeList(NodeList& other):
    length(other.length)
{   
    Node* nodeCopy;
    for (int i=0; i < other.getLength(); ++i) {
        nodeCopy = new Node(*other.getNode(i));
        nodes[i] = nodeCopy;
    }
}  

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){

    Node* node = new Node(*newPos);
    if (length == 0) 
    {
        nodes[0] = node;
        ++length;
    } else {
        nodes[length] = node;
        ++length;
    }  
}

Node* NodeList::getNode(int i){
    return nodes[i];
}