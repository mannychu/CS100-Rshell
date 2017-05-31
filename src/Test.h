#ifndef TEST_H
#define TEST_H

#include <vector>
#include <string>
#include "Legacy.h"

using namespace std;

class Test : public Legacy
{
    private:
        string command;
        
    public:
    
    //Constructors
    
        Test();
        
        Test(string command);
        
    //Functions
    
        bool execute();
        
        string getData();
};


#endif 