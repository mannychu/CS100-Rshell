#ifndef LT_H
#define LT_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Input.h"

using namespace std;

class Lt : public Input {
private:
    Input* left;
    string right;
public:
    Lt();
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif