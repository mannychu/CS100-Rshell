#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Pipe.h"

Pipe::Pipe() 
{
    left = 0;
    right = "";
}

void Pipe::setLeft(Legacy* left) 
{ 
    this->left = left; 
}

void Pipe::setRight(string right) 
{ 
    this->right = right; 
}

bool Pipe::execute() 
{
    //beign pipe
    int pipe1[2];
    pipe(pipe1);
    
    if (right.at(0) == ' ') 
    {
        unsigned it = 0;
        while (right.at(it) == ' ') 
        {
            it++;
        }
        right = right.substr(it);
    }

    if (right.at(right.size()-1) == ' ') 
    {
        unsigned it = right.size()-1;
        while (right.at(it) == ' ') 
        {
            it--;
        }
        right = right.substr(0, it+1);
    }

    // convert this to a Cstring
    char* cmd_cstr = (char*)right.c_str();
    vector<char*> arguments;

    char* tmp_cstr;
    tmp_cstr = strtok(cmd_cstr, " ");

    while (tmp_cstr != NULL) 
    {
        if (tmp_cstr != '\0')
        {
            arguments.push_back(tmp_cstr);
        }
        
        tmp_cstr = strtok(NULL, " ");
    }

    char** args = new char*[arguments.size()+1];

    for (unsigned i = 0; i < arguments.size(); i++) 
    {
        args[i] = arguments.at(i);
    }
    args[arguments.size()] = NULL;

    int status; //location memory of status

    int outFile = dup(1);
    if (outFile == -1) 
    {
        perror("dup out");
        return false;
    }

    int inFile = dup(0);
    if (inFile == -1) 
    {
        perror("dup in");
        return false;
    }

    if (dup2(pipe1[1], 1) == -1) 
    {
        perror("out dup2");
        return false;
    }

    if (dup2(pipe1[0], 0) == -1) 
    {
        perror("in dup2");
        return false;
    }

    bool checkLeft = left->execute();

    if (dup2(outFile, 1) == -1) 
    {
        perror("checkLeft is coming back");
        return false;
    }

    if (close(pipe1[1]) == -1) 
    {
        perror("close 1");
        return false;
    }

    if (!checkLeft) {
        return false;
    }

    
    pid_t pid = fork(); 

    // Fork ERROR
    if (pid == -1) 
    {
        perror("fork failed");
        exit(1);
    }

    // CHILD PROCESS CALLS EXECVP
    if (pid == 0) 
    {
        // Execute right side
        if (execvp(args[0], args) == -1) 
        {
            perror("exec");
            exit(1);
        }
        // Unconditional kill
        exit(1);
    }

    // no longer needed args so freeing up space as 
    //good coders should
    delete[] args;

    //be good to your parents, parent process :0
    if (pid > 0) 
    {
        if (close(pipe1[0]) == -1) 
        {
            perror("close 0");
            return false;
        }

        waitpid(pid, &status, 0);
      
        if (dup2(inFile, 0) == -1) 
        {
            perror("rightside restore");
            return false;
        }  
        if (status > 0) // executevp has failed s it comes down to this..
        {
            return false;
        }
        else if (WEXITSTATUS(status) == 0)  // GOOD TO GO
        {
            return true;
        }
        else if (WEXITSTATUS(status) == 1)  // FAILED, TRY AGAIN
        {
            return false;
        }

    }
    return false; 
}