#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class Instruction
{
    // memory
    PushReg = 1, PushVal, SetReg, SetVal, Pop,

    // math
    Add, Sub, Mul, Div,

    Stop,

    // registers
    A = 256, B, C, D, E, F, G, H
};

class Parser
{
private:
    vector<string> tokens;
    map<string, Instruction> instrByToken;
public:
    Parser();
    Parser(vector<string> tokens);

    void setTokens(vector<string> tokens);
    vector<string> getTokens();

    vector<Instruction> parse();
};