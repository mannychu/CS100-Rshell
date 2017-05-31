#ifndef SEMICOLON_H
#define SEMICOLON_H

#include "Connect.h"
#include "Legacy.h"

class Semicolon : public Connector
{
    public:
    
    //Constructors
    
        Semicolon();
        
        Semicolon(Legacy* leftChild, Legacy* rightChild);
    
    //Functions
    
        void setleftChild(Legacy* leftChild);
        
        void setrightChild(Legacy* rightChild);
        
        bool execute();
};

#endif