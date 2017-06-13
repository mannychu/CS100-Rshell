#ifndef DUBRT_H	
#define DUBRT_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Input.h"

using namespace std;

class DubRt : public Input {
private:
    Input* left;
    string right;
public:
    DubRt();
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif
