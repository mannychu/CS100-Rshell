#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Rt.h"

Rt::Rt() 
{
	left = 0;
	right = "";
}

void Rt::setLeft(Legacy* left) 
{ 
	this->left = left; 
}

void Rt::setRight(string right) 
{ 
	this->right = right; 
}

bool Rt::execute() 
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

	// Retain stdinput 
	int buffer = dup(1);
	
	//Open new file for output
	int outFile = open(right.c_str(), O_CREAT|O_RDWR);
	
	//Return an error if the file is not opened
	if (outFile == -1) 
	{
		perror("Error: Unable to open OUT file.");
		return false;
	}

	close(1);
	dup2(outFile, 1);

	//execute command 
	bool finalEx = left->execute();

	close(1);
	dup2(buffer, 1);
	
	return finalEx;
}