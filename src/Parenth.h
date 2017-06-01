#ifndef PARENTH_H
#define PARENTH_H

#include "Connect.h"
#include "Legacy.h"

class Parenth : public Connector
{
    public:
    
    //Constructors
    
        Parenth(Legacy* paren);
    
    //Functions
        
        bool execute();
    
    //Variables
        
        Legacy* parenthObj;
        
};

#endif
