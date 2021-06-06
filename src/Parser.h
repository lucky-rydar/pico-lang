#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum class Instruction
{
    Push = 1, Pop, Set,
    Add, Sub, Mul, Div
};

enum class Register
{
    A = 256, B, C, D, E, F, G, H
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