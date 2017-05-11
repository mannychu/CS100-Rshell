#ifndef CMD_H
#define CMD_H

#include <vector>
#include <string>
#include "Legacy.h"

using namespace std;

class CMD : public Legacy
{
    private:
        string command;
        
    public:
    
    //Constructors
    
        CMD();
        
        CMD(string command);
        
    //Functions
    
        bool execute();
        
        string getData();
};

#endif