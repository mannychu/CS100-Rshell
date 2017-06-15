#ifndef LT_H
#define LT_H

#include "Legacy.h"

#include <string>
#include <stdio.h>
#include <unistd.h>

using namespace std;

class Lt : public Legacy {
	
	private:

	    Legacy* left;
	    string right;

	public:

	    Lt();
	    void setLeft(Legacy* left);
	    void setRight(string right);
	    bool execute();
};

#endif