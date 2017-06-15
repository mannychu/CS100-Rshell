#ifndef Rt_H
#define Rt_H

#include <string>
#include <stdio.h>
#include <unistd.h>

#include "Legacy.h"

using namespace std;

class Rt : public Legacy 
{
	private:
	    Legacy* left;
	    string right;
	
	public:
	    Rt();
	    void setLeft(Legacy* left);
	    void setRight(string right);
	    bool execute();
};

#endif
