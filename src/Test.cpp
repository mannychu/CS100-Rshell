#include "Legacy.h"
#include "Test.h"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include <vector> 
#include <string.h>

using namespace std;

// Constructors
Test::Test() {}

Test::Test(string command) {this->command = command;}

string Test::getData() {return command;}

//execute test with appropriate flag, -e will be tested if no flag is given
//-e tests if either file or directory,
//-f tests if file
//-d tests if directory
bool Test::execute()
{
    cout << "test command: " << command << endl;
    bool fileFound = false;
    bool directoryFound = false;
    string flag = "";
    const char* pathname = new char[command.length() + 1];
    
    struct stat sb;
    
    if(command[0] == '-')
    {
        //separate flag from argument
        flag = command.substr(0, 2);
        command = command.substr(3, command.size() - 1);
        
        //eliminate whitespace
        for(unsigned i = 0; i < command.length(); i++)
        {
            if(command[i] == ' ')
            {
                command.erase(i, i);
            }
        }
        
        //copy to pathname
        pathname = command.c_str();
        
    }
    else if(command[1] == '-')                                                      //{
    {                                                                                   //This chunk is probably not necessary,
        //separate flag from argument                                                   //just sort of a precaution
        flag = command.substr(1, 3);
        command = command.substr(4, command.size() - 1);
        
        //eliminate whitespace
        for(unsigned i = 0; i < command.length(); i++)
        {
            if(command[i] == ' ')
            {
                command.erase(i, i);
            }
        }
        
        //copy to pathname
        pathname = command.c_str();
    }                                                                               //}
    else    
    {
        //eliminate whitespace
        for(unsigned i = 0; i < command.length(); i++)
        {
            if(command[i] == ' ')
            {
                command.erase(i, i);
            }
        }
        
        //copy to pathname
        pathname = command.c_str();
    }
    

    cout << "pathname: " << pathname << endl;
    cout << "flag: " << flag << endl;
    
    if(flag == "-d")
    {
        if(stat(pathname, &sb) == 0 && S_ISDIR(sb.st_mode))
        {
            cout << "(True)" << endl;
            return true;
        }
    }
        
    if(flag == "-f")
    {
        if(stat(pathname, &sb) == 0 && S_ISREG(sb.st_mode))
        {
            cout << "(True)" << endl;
            return true;
        }
    }
    
    if(flag == "-e" || flag == "")
    {
        
        if(stat(pathname, &sb) == 0)
        {
            fileFound = true;
        }
        
        if(stat(pathname, &sb) == 0)// && S_ISDIR(sb.st_mode))
        {
            directoryFound = true;
        }
        
        if(fileFound || directoryFound)
        {
            cout << "(True)" << endl;
            return true;
        }
    }
    
    cout << "(False)" << endl;
    return false;
}

