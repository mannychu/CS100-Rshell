#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include <string.h>

#include "Cmd.h"
#include "Legacy.h"

using namespace std;

// Constructors
CMD::CMD() {}

CMD::CMD(string command) {this->command = command;}

string CMD::getData() {return command;}

bool CMD::execute() 
{
    if (command.at(0) == ' ') {                 //delete whitespace
        unsigned it = 0;
        while (command.at(it) == ' ') {
            it++;
        }
        command = command.substr(it);
    }

    if (command.at(command.size()-1) == ' ') {  //remove whitespace at the end
        unsigned it = command.size()-1;
        while (command.at(it) == ' ') {
            it--;
        }
        command = command.substr(0, it+1);
    }

    if (command == "exit" || command == "q")    //check for exit
        exit(0);

    char* cmd_cstr = (char*)this->command.c_str();
    vector<char*> arguments;
    char* p;
    p = strtok(cmd_cstr, " ");
    while (p != NULL) {
        if (p != '\0')
            arguments.push_back(p);
        
        p = strtok(NULL, " ");
    }

    // Char* array to be passed to execvp()
    char** args = new char*[arguments.size()+1];

    for (unsigned i = 0; i < arguments.size(); i++) {
        args[i] = arguments.at(i);
    }
    args[arguments.size()] = NULL;

    int status;         // status for pid
    pid_t pid = fork(); // create child process

    if (pid == -1) {        //error with fork
        perror("fork failed");
        exit(1);
    }

    // Child process, calls execvp()
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("exec");
            exit(1);
        }
    }

    // Deallocating char** b/c no longer needed
    delete[] args;

    // Parent process
    if (pid > 0) {
        waitpid(pid, &status, 0);
        if (status > 0) // If status returned, execvp failed
            return false;
        else if (WEXITSTATUS(status) == 0)  // Successful execution
            return true;
        else if (WEXITSTATUS(status) == 1)  // Unsuccessful execution
            return false;
        
    }

    // Shouldn't be hit
    return false;
}