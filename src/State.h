#pragma once
#include <stack>
#include <vector>

#include "Parser.h"

using namespace std;

class State
{
private:
    stack<int> stackMem;
    int A, B, C, D, E, F, G, H;

public:
    State();
    
    void setRegVal(Instruction reg, int val);
    int getRegVal(Instruction reg);

    void pushVal(int val);
    void popVal(Instruction reg);
};