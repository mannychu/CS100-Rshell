#ifndef PIPE_H
#define PIPE_H

#include <stdio.h>
#include <string>
#include <unistd.h>

#include "Legacy.h"

using namespace std;

class Pipe : public Legacy 
{
	private:

	    Legacy* left;
	    string right;

	public:

	    Pipe();
	    void setLeft(Legacy* left);
	    void setRight(string right);
	    bool execute();
};

#endif