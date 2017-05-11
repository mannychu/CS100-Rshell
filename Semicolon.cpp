#include "Semicolon.h"
#include "Connect.h"
#include "Legacy.h"

//Constructors
Semicolon::Semicolon() : Connector() 
{
    leftChild = 0;
    rightChild = 0;
}

Semicolon::Semicolon(Legacy* leftChild, Legacy* rightChild) : Connector(leftChild,rightChild) 
{
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

void Semicolon::setleftChild(Legacy* leftChild) 
{
    this->leftChild = leftChild;
}

void Semicolon::setrightChild(Legacy* rightChild) 
{
    this->rightChild = rightChild;
}

bool Semicolon::execute() 
{
    leftChild->execute();   //everything executes
    rightChild->execute();
    
    return true;
}