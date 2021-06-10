#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class Instruction
{
    // memory
    Push, Set, Pop,

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
    map<string, function<void(vector<Instruction>&, int &index)>> parserByToken;

    void parsePush(vector<Instruction>& ins, int &index);
    void parsePop(vector<Instruction>& ins, int &index);
    void parseSet(vector<Instruction>& ins, int &index);
    
    void parseAdd(vector<Instruction>& ins, int &index);
    void parseSub(vector<Instruction>& ins, int &index);
    void parseMul(vector<Instruction>& ins, int &index);
    void parseDiv(vector<Instruction>& ins, int &index);

    void parseStop(vector<Instruction>& ins, int index);
public:
    Parser();
    Parser(vector<string> tokens);

    void setTokens(vector<string> tokens);
    vector<string> getTokens();

    vector<Instruction> parse();
};