#include "Legacy.h"
#include "Connect.h"
#include "Parenth.h"

using namespace std;


//Constructor
Parenth::Parenth(Legacy* paren)
{
    this->parenthObj = paren;
    return;
}

bool Parenth::execute() 
{
    return parenthObj->execute();
}
