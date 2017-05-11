#ifndef CONNECT_H
#define CONNECT_H

#include <iostream>
#include <cstdlib>

#include "Legacy.h"

using namespace std;

class Connector : public Legacy
{

    protected:  //sub classes able to use these as well
    
        Legacy* leftChild;
        Legacy* rightChild;
    
    public:
    
    //Construtors
    
        Connector();
        Connector(Legacy* leftChild, Legacy* rightChild);
    
    //Functions  
    
        virtual bool execute() = 0;
};

#endif