#ifndef PARENTH_H
#define PARENTH_H

#include "Connect.h"
#include "Legacy.h"

class Parenth : public Connector
{
    public:
    
    //Constructors
        
        Parenth();
        
        Parenth(Legacy* obj);
    
    //Functions
        
        bool execute();
        void setChild(Legacy* obj);
        
        Legacy* parenthObj;
        
};

#endif