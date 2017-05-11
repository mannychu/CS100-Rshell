#ifndef OR_H
#define OR_H

#include "Connect.h"
#include "Legacy.h"

class OR : public Connector
{
    public:
    
    //Constructors
    
        OR();
        
        OR(Legacy* leftChild, Legacy* rightChild);
    
    //Functions
    
        void setLeftChild(Legacy* leftChild);
        
        void setRightChild(Legacy* rightChild);
        
        bool execute();
};

#endif