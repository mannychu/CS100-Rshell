#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Lt.h"

Lt::Lt() //: left(0), right("") {}
{
	left = 0;
	right = "";
}

void Lt::setLeft(Legacy* left) 
{ 
	this->left = left; 
}

void Lt::setRight(string right) 
{ 
	this->right = right; 
}

bool Lt::execute() 
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

	//Retain stdinput
	int buffer = dup(0);
	
	//Opens new file for output
	int outFile = open(right.c_str(), O_RDWR);
	
	//Return an error if the file is not opened
	if (outFile == -1) 
	{
		perror("Error: Unable to open IN file.");
		return false;
	}

	close(0);
	dup2(outFile, 0);

	// execute command
	bool finalEx = left->execute();

	close(0);
	dup2(buffer, 0);
	
	return finalEx;
}