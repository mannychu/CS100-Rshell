#include "Legacy.h"
#include "Connect.h"
#include "Parenth.h"

using namespace std;

//Empty Constructor
Parenth::Parenth() : Connector() {}

//Constructor
Parenth::Parenth(Legacy* obj)
{
    this->parenthObj = obj;
    return;
}



void Parenth::setChild(Legacy* obj)
{
    this->parenthObj = obj;
    return;
}

bool Parenth::execute() 
{
    if(parenthObj->execute())             //neither succeeded
    {
        return true;
    }
    else
    {
        return false;
    }
}