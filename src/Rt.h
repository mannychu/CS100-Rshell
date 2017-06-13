#ifndef Rt_H
#define Rt_H

#include <unistd.h>
#include <string>
#include <stdio.h>
#include "Input.h"

using namespace std;

class Rt : public Input {
private:
    Input* left;
    string right;
public:
    Rt();
    void setLeft(Input* l);
    void setRight(string r);
    bool evaluate();
};

#endif