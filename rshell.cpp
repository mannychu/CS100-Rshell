//
//
//          Assignment 1/2 - Design a 'bash' shell 
//
//              David Weber & Immanuel Chu
//                      5/10/17
//
//

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <unistd.h>

#include "Legacy.h"
#include "Cmd.h"
#include "Connect.h"
#include "And.h"
#include "Or.h"
#include "Semicolon.h"

using namespace std;

void parseInput(string&, Legacy*&);
bool checkForSpace(const string& input);
void makeTree(Legacy*&, vector<char>&, vector<string>&);
Legacy* treeUtility(vector<char>& connectors, vector<string>& commands);

//checks input string for spaces in conjunction with #comments in other part
bool checkForSpace(const string& input) 
{
    for (unsigned i = 0; i < input.size(); i++) 
    {
        if(input.at(i) == '#') 
        {
            return true;
        }
        else if( (input.at(i) != ' ') && (input.at(i) != '#') )
        {
            return false;
        }
    }

    return true;
}

void parseInput(string &input, Legacy* &inputs)
{
    //VARS 
    bool commentFound = false;
    bool commandPush = false;
    vector<char> connectors;
    vector<string> commands;
    unsigned begin = 0;
    
    //check if '#' entered
    for(unsigned i = 0; i < input.size() && commentFound != true; ++i) 
    {
        if(input.at(i) == '#') 
        {
            input = input.substr(begin, i - begin);
            commentFound = true;
        }
    }
    
    // gets rid of whitespace
    if(input.at(input.size() - 1) == ' ') 
    {
        unsigned i = input.size() - 1;
        
        while(input.at(i) == ' ') 
        {
            i--;
        }
        
        input = input.substr(0, i + 1);
    }
    
    for(unsigned i = 0; i < input.size(); ++i) 
    {
        // command found??
        if(commandPush) 
        {
            while(input.at(i) == ' ' && i < input.size()) 
            {
                if(i != input.size() - 1) 
                {
                    ++i;
                    ++begin;
                }
            }
            commandPush = false;
        }
        
        // detects semicolon
        if(input.at(i) == ';') 
        {
            connectors.push_back(input.at(i));
            commands.push_back(input.substr(begin, i - begin));
            begin = i + 1;
            commandPush = true;
        }
        else if(input.at(i) == '&' && i < (input.size() - 1)) 
        {
            if(input.at(i + 1) == '&') 
            {
                connectors.push_back(input.at(i));
                commands.push_back(input.substr(begin, i - begin));
                begin = i + 2;
                commandPush = true;
            }
        }

        else if(input.at(i) == '|' && i < (input.size() - 1)) 
        {
            if(input.at(i + 1) == '|') 
            {
                connectors.push_back(input.at(i));
                commands.push_back(input.substr(begin, i - begin));
                begin = i + 2;
                commandPush = true;
            }
        }
        else if(!connectors.empty() && !commands.empty() && i == input.size() - 1 && input.at(input.size() - 1) != ';') 
        {
            commands.push_back(input.substr(begin, input.size()));
        }
    }
    
    if(!connectors.empty() && connectors.back() == ';' && commands.back() == "") 
    {
        connectors.pop_back();
        commands.pop_back();
    }

    
    if(connectors.size() == 0)      //single command
    {
        commands.push_back(input.substr(begin, input.size() - begin));
    }
    
    makeTree(inputs, connectors, commands);
    
    return;
}

void makeTree(Legacy*& inputs, vector<char>& connectors, vector<string>& commands)
{
    for(unsigned i = 0; i < commands.size(); i++) // Removes all the empty commands
    {  
        if(commands.at(i) == "") 
        {
            commands.erase(commands.begin() + i - 1);
        }
    }
    
    if(commands.size() == 1) //if single command
    {
        Legacy* in = new CMD(commands.at(0));
        inputs = in;
        in = 0;
        return;
    }
    
    inputs = treeUtility(connectors, commands);
    return;
}

Legacy* treeUtility(vector<char>& connectors, vector<string>& commands) 
{
   
    if(commands.size() == 1 && connectors.empty())  // Legacy case, returns a Command
    { 
        // cout << "Legacy" << endl;
        return new CMD(commands.at(0));
    }
    
    if (connectors.back() == '&')
    {
        connectors.pop_back();
        AND* connector = new AND(); //creat new AND
        
        connector->setrightChild(new CMD(commands.back())); //set right
        commands.pop_back();
        
        connector->setleftChild(treeUtility(connectors, commands)); //set left

        return connector;
    }
    
    if (connectors.back() == ';') 
    {
        connectors.pop_back();
        Semicolon* connector = new Semicolon(); //create new SEMI
        
        connector->setrightChild(new CMD(commands.back())); //set right
        commands.pop_back();
        connector->setleftChild(treeUtility(connectors, commands)); //set left
        return connector;
    }


    if (connectors.back() == '|') 
    {
        connectors.pop_back();
        
        OR* connector = new OR();   //create new OR
        connector->setRightChild(new CMD(commands.back())); //set right child
        commands.pop_back();        
        
        connector->setLeftChild(treeUtility(connectors, commands)); //set left
        
        return connector;
    }
    

    return 0;
}



int main()
{
    string entireLine;  //initialize string for input

    Legacy* inputs = 0;
    
    for ( ; ; )         //continute until...
    {
        
        cout << "$ ";   //bash AESTHETIX
        getline(cin, entireLine);   //get user input
        
        if((entireLine == "") || (checkForSpace(entireLine))) 
        {
            continue;
        }
        try 
        {
            parseInput(entireLine, inputs); //parse
            inputs->execute();
        }
        catch(string s) 
        {
            cout << s << endl;
            continue;
        }
        
    }
    
    return 0;
}
