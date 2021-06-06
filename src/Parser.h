#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum class Instruction
{
    Push = 1, Pop, Set,
    Add, Sub, Mul, Div
};

class Parser
{
private:
    vector<string> tokens;
public:
    Parser();
    Parser(vector<string> tokens);

    void setTokens(vector<string> tokens);
    vector<string> getTokens();

    vector<Instruction> getBytes();
};