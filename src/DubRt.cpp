#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "DubRt.h"

DubRt::DubRt() 
{
	left = 0;
	right = "";
}


void DubRt::setLeft(Legacy* left) 
{ 
	this->left = left; 
}

void DubRt::setRight(string right) 
{ 
	this->right = right; 
}

bool DubRt::execute() 
{
	// Remove whitespace by incrementing string by one position
    if (right.at(0) == ' ') 
    {
        unsigned it = 0;
        while (right.at(it) == ' ') 
        {
            it++;
        }
        right = right.substr(it);
    }

	// Remove whitespace by deleting empty 'spaces'
    if (right.at(right.size()-1) == ' ') 
    {
        unsigned it = right.size()-1;
        while (right.at(it) == ' ') 
        {
            it--;
        }
        right = right.substr(0, it+1);
    }

	//Retains stdinput
	int buffer = dup(1);
	
	int outFile = open(right.c_str(), O_CREAT|O_APPEND|O_RDWR);
	
	//Return error if file is not opened
	if (outFile == -1) 
	{
		perror("Error: Unable to open OUT file");
		return false;
	}

	close(1);
	dup2(outFile, 1);

	// execute command
	bool finalEx = left->execute();

	close(1);
	dup2(buffer, 1);
	
	return finalEx;
}

