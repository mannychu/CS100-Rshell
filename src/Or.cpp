#include "Or.h"
#include "Connect.h"

// Constructors
OR::OR() : Connector() {}

OR::OR(Legacy* leftChild, Legacy* rightChild) : Connector(leftChild, rightChild) {
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

void OR::setLeftChild(Legacy* leftChild) {
    this->leftChild = leftChild;
}

void OR::setRightChild(Legacy* rightChild) {
    this->rightChild = rightChild;
}

bool OR::execute() {
    if (!(leftChild->execute())) {      //if leftchild does not work
        if (rightChild->execute()) {    //execute rightchild
            return true;                //if rightchild succeeds, return true
        }
        else {
            return false;               //else return false
        }
    }
    return false;
}