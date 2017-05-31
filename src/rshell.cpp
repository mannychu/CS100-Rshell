//
//
//          Assignment 1/2/3 - Design a 'bash' shell 
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
#include "Test.h"
#include "Parenth.h"

using namespace std;

void parseInput(string&, Legacy*&);
void testProtocol(string&, Legacy*&);
bool checkForSpace(const string& input);
void makeTree(Legacy*&, vector<char>&, vector<string>&, bool);
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

void testProtocol(string& input, Legacy* &inputs)
{
    cout << "yolo" << endl;
    return;
}

void parseInput(string &input, Legacy* &inputs)
{
    bool commentFound = false;
    //bool parenFound = false;
    bool commandPush = false;
    bool leftbracketFound = false;
    bool testSignaled = false;
    vector<char> connectors;
    vector<string> commands;
    unsigned begin = 0; //beginning index. this will increment as the input is parsed to create the "new" input
    
    //check if '#' entered
    for(unsigned i = 0; i < input.size() && commentFound != true; ++i)  //run until end of input or until comment is found 
    {
        //cout << "1" << endl;
        if(input.at(i) == '#') //comment found
        {
            input = input.substr(begin, i - begin); //input is now substring from beginning until comment
            commentFound = true; //set comment flag to true
        }
    }//END FOR
    
    //check if '[' entered
    for(unsigned i = 0; i < input.size() && leftbracketFound != true; ++i) //run until end of input or left bracket is found
    {
        //cout << "2" << endl;
        if(input.at(i) == '[') //bracket found
        {
            input.erase(0, 2);   //erase
            leftbracketFound = true;   //set bracket flag to true
        }
    }//END FOR
    
    
    
    
    // gets rid of whitespace
    if(input.at(input.size() - 1) == ' ') //if end of input is a whitespace
    {
        //cout << "3" << endl;
        unsigned i = input.size() - 1; //set i = last index of input
        
        while(input.at(i) == ' ')   //while last index of input is whitespace
        {
            i--;  //set new index of i to not have whitespace
        }
        
        input = input.substr(0, i + 1);   //new input is now input without whitespaces (takes on i index)
    }//END IF
    
    for(unsigned i = 0; i < input.size(); ++i)  //run through whle input
    {
        //cout << "4" << endl;
        if(commandPush) //if commandPush flag is true
        {
            //cout << "5" << endl;
            while(input.at(i) == ' ' && i < input.size())   //while input @ index i is whitespace and i < inputsize
            {
                if(i != input.size() - 1) //while i is not inputsize
                {
                    ++i;   //increment whole array to make "new" input
                    ++begin;  //by incrementing i and begin
                }
            }
            commandPush = false; //set commandPush flag to false
        }
        
        //check for semicolon
        if(input.at(i) == ';')   //if semicolon
        {
            //cout << "6" << endl;
            connectors.push_back(input.at(i));  //pushback ';' connector
            commands.push_back(input.substr(begin, i - begin));   //pushback commands using index i
            begin = i + 1; //set new being
            commandPush = true;  //command was pushed
        }
        
        //check for ending brackets
        //leftbracketFound is set above so need only check for right 
        else if(input.at(i) == ']' && leftbracketFound)  //if input at i is ']' and leftbracket exists              
        {
            //cout << "7" << endl;
            commands.push_back(input.substr(begin, i - begin));   //pushback input from begin to i - begin
            begin = i + 3; //increment begin to make "new" input
            testSignaled = true; //set testSignaled flag to true
            commandPush = true;  //set commandPush flag to true
        }  
        
        //check for ending parantheses
        //left paren is set above so need only check for right
        else if(input.at(i) == '(')
        {
            connectors.push_back(input.at(i));
            commands.push_back(input.substr(begin, i - begin));
            begin = i + 1;
            commandPush = true;
        }
        else if(input.at(i) == ')')
        {
            /* FIX
            cant just pushback, as paren places it in the front
            */
            connectors.push_back(input.at(i));
            commands.push_back(input.substr(begin, i - begin));   //pushback input from begin to i - begin
            begin = i + 1; //increment begin to make "new" input
            commandPush = true;  //set commandPush flag to true
        }
        
        //check for connecter '&'                    
        else if(input.at(i) == '&' && i < (input.size() - 1)) //if '&' is found and there is still some of input to parse
        {
            //cout << "8" << endl;
            if(input.at(i + 1) == '&')  //check for the second "&" ex. "&&" instead of just '&'
            {  
                //cout << "9" << endl;
                connectors.push_back(input.at(i)); //push back connector '&'
                commands.push_back(input.substr(begin, i - begin));  //pushback commands from begin to i - begin
                begin = i + 2;   //increment begin by 2 to make up for "&&"
                commandPush = true; //set commandPush to true
            }
        }
        
        //check for connector '|'
        else if(input.at(i) == '|' && i < (input.size() - 1))  //if '|' is found and there is still some of input to parse
        {
            //cout << "10" << endl;
            if(input.at(i + 1) == '|') //if second '|' exists
            {
                //cout << "11" << endl;
                connectors.push_back(input.at(i)); //push back command at index i
                commands.push_back(input.substr(begin, i - begin));  //pushback commands from begin to i - begin
                begin = i + 2;   //increment begin by 2 to make up for "||"
                commandPush = true; //set commandPush flag to true
            }
        }
        //if connectors, commands are not empty, and no more input to parse, and last char is NOT ';', and testSignaled is false
        else if(!connectors.empty() && !commands.empty() && i == input.size() - 1 && input.at(input.size() - 1) != ';' && !testSignaled) 
        {
            //cout << "12" << endl;
            commands.push_back(input.substr(begin, input.size()));   //pushback the whole input. input has no connectors, simply one command
        }
    }//END FOR
    
    //last element of connectors is not empty and ';'
    if(!connectors.empty() && connectors.back() == ';' && commands.back() == "") 
    {
        //cout << "13" << endl;
        connectors.pop_back();   //get rid of ';' in connectors
        commands.pop_back();  //get rid of last element in commands
    }//END IF

    //if connectors has nothing and testSignaled is false
    if(connectors.size() == 0 && !testSignaled) //single command
    {
        //cout << "14" << endl;
        commands.push_back(input.substr(begin, input.size() - begin));  //pushback single command
    }// END IF
    
    makeTree(inputs, connectors, commands, testSignaled);   //make tree with executes
    
    return;
}

void makeTree(Legacy*& inputs, vector<char>& connectors, vector<string>& commands, bool testSignaled)
{
    
    for(unsigned i = 0; i < commands.size(); i++) //runs through commands and removes empty commands
    {  
        if(commands.at(i) == "") //if empty command
        {
            commands.erase(commands.begin() + i - 1); //erase empty commands
        }
    }
    
    if((commands.size() == 1) && testSignaled)  //if command has only one element, and testsignaled = true
    {
        Legacy* in = new Test(commands.at(0));  //make new Test object
        inputs = in; //inputs 
        in = 0; //set in to 0
        return;
    }
    
    else if(commands.size() == 1) //if single command
    {
        Legacy* in = new CMD(commands.at(0));
        inputs = in;
        in = 0;   //reset in
        return;
    }
    
    inputs = treeUtility(connectors, commands); //create executables..?
    return;
}


Legacy* treeUtility(vector<char>& connectors, vector<string>& commands) 
{
    if(commands.size() == 1 && connectors.empty())  // Base Legacy case, returns a Command
    { 
        // cout << "Legacy" << endl;
        return new CMD(commands.at(0));
    }
    
    if (connectors.back() == '&')   //if last element of connectors is '&', create AND object
    {
        connectors.pop_back();   //delete last object, in this case '&'. this is possible because there are two '&'
        AND* connector = new AND(); //creat new AND object
        
        connector->setrightChild(new CMD(commands.back())); //simultaneously create new CMD of last element of commands and set it as connector's right child
        commands.pop_back();  //delete commands last element
        connector->setleftChild(treeUtility(connectors, commands)); //recursively call treeUtility using updated connectors and commands

        return connector; //input = connector
    }
    
    if (connectors.back() == ';')   //if last element is ';'
    {
        connectors.pop_back();  //delete ';'
        Semicolon* connector = new Semicolon(); //create new Semicolon object
        
        connector->setrightChild(new CMD(commands.back())); //simultaneously create CMD using last element of commands and set it as connector's right child
        commands.pop_back();  //delete commands last element
        connector->setleftChild(treeUtility(connectors, commands)); //recursively call treeUtility using updated connectors and commands

        return connector;  //input = connector
    }
    
    if(connectors.back() == ')')
    {
        connectors.pop_back();
        
        while(connectors.back() != '(')
        {
            if (connectors.back() == '&')   //if last element of connectors is '&', create AND object
            {
                connectors.pop_back();   //delete last object, in this case '&'. this is possible because there are two '&'
                AND* connector = new AND(); //creat new AND object
                
                connector->setrightChild(new CMD(commands.back())); //simultaneously create new CMD of last element of commands and set it as connector's right child
                commands.pop_back();  //delete commands last element
                connector->setleftChild(treeUtility(connectors, commands)); //recursively call treeUtility using updated connectors and commands
                
                Parenth* connector2 = new Parenth(connector);
                return connector2;
            }
            
            if (connectors.back() == '|') //if last element is '|'
            {
                connectors.pop_back();   //delete last element of connectors
                OR* connector = new OR();   //create new OR object
        
                connector->setRightChild(new CMD(commands.back())); //simultaneously create CMD using last element of commands and set it as connector's right child
                commands.pop_back();  //delete commands last element 
        
                connector->setLeftChild(treeUtility(connectors, commands)); //recursively call treeUtility using updated connectors and commands
                
                Parenth* connector2 = new Parenth(connector);
                return connector2;
            }
        }
        
    }


    if (connectors.back() == '|') //if last element is '|'
    {
        connectors.pop_back();   //delete last element of connectors
        OR* connector = new OR();   //create new OR object

        connector->setRightChild(new CMD(commands.back())); //simultaneously create CMD using last element of commands and set it as connector's right child
        commands.pop_back();  //delete commands last element 

        connector->setLeftChild(treeUtility(connectors, commands)); //recursively call treeUtility using updated connectors and commands
        
        return connector;  //input = connector
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
