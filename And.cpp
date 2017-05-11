#include "Legacy.h"
#include "Connect.h"
#include "And.h"



//Empty Constructor
AND::AND() : Connector() {}

//Constructor
AND::AND(Legacy* leftChild, Legacy* rightChild) : Connector(leftChild, rightChild) {
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}


void AND::setleftChild(Legacy* leftChild) {
    this->leftChild = leftChild;    //set leftChild 
}

void AND::setrightChild(Legacy* rightChild) {
    this->rightChild = rightChild;  //set rightChild
}

bool AND::execute() {
    if (leftChild->execute()) {      //if left side succeeds
        if (rightChild->execute()) { //try right side
            return true;             //if right side succeeds too, return true
        }                       
        else {                  
            return false;           //only left side succeeded
        }       
    }
    return false;               //neither succeeded
}