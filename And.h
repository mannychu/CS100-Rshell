#ifndef AND_H
#define AND_H

#include "Connect.h"
#include "Legacy.h"

class AND : public Connector
{
    public:
    
    //Constructors
        
        AND();
        
        AND(Legacy* leftChild, Legacy* rightChild);
    
    //Functions
    
        void setleftChild(Legacy* leftChild);
        
        void setrightChild(Legacy* rightChild);
        
        bool execute();
};

#endif