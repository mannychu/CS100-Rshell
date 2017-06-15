#ifndef DUBRT_H	
#define DUBRT_H

#include <string>
#include <stdio.h>
#include <unistd.h>

#include "Legacy.h"

using namespace std;

class DubRt : public Legacy 
{
	private:

	    Legacy* left;
	    string right;

	public:
    
	    DubRt();
	    void setLeft(Legacy* left);
	    void setRight(string right);
	    bool execute();

};

#endif
