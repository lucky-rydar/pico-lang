#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include <map>

#include "ArgumentParser.h"

using namespace std;

enum class Instruction
{
    // memory
    Push = 1, Pop, Set,

    // math
    Add, Sub, Mul, Div,

    Stop,

    // registers
    A = -1, B = -2, C = -3, D = -4, 
    E = -5, F = -6, G = -7, H = -8
};

class Parser
{
    typedef ArgumentParser ArgPars;
private:
    vector<string> tokens;
    map<string, Instruction> registerByToken;

    map<string, function<void(int &index)>> parserByToken;
    
    vector<int> compiled;
    vector<int> staticMem;

private:
    void parsePush(int &index);
    void parsePop(int &index);
    void parseSet(int &index);
    
    void parseAdd(int &index);
    void parseSub(int &index);
    void parseMul(int &index);
    void parseDiv(int &index);

    void parseStop(int &index);

public:
    Parser();
    Parser(vector<string> tokens);

    void setTokens(vector<string> tokens);
    vector<string> getTokens();

    vector<int> parse();

    static void ensureIntValid(string val);
};