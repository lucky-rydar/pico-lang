#pragma once
#include <functional>
#include <iostream>
#include <vector>
#include <regex>
#include <map>

#include "ArgumentParser.h"
#include "Bytecode.h"

using namespace std;

enum class Instruction
{
    // memory
    Push = 1, Pop, Set,

    // math
    Add, Sub, Mul, Div,

    Stop,

    // i/o
    In, Out, Outl,

    // jump
    Jump, // jump anyway
    
    // jump with condition
    Je, // jump if equal ==
    Jm, // jump if left more > 
    Jl, // jump if left less <
    Jme, // jump if left more or equal >=
    Jle, // jump if left less or equal <=
    Jne, // jump if not equal !=

    Pass, // do nothing

    Cmp, // do compare

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
    map<string, function<void()>> parserByToken;
    
    Bytecode bytecode;

    int ct; // current token

    map<string, int> marks;
private:
    void parsePush();
    void parsePop();
    void parseSet();
    
    void parseAdd();
    void parseSub();
    void parseMul();
    void parseDiv();

    void parseStop();

    void parseIn();
    void parseOut();
    void parseOutl();

    void parseMark();
    void parsePass();
    void parseJump();
    void parseCmp(); // means compare

    void processMetadata();
    void processMarks();

    void parseValRegArg(string arg);
    void parseRegArg(string arg);
    void parseValArg(string arg);
public:
    Parser();
    Parser(vector<string> tokens);

    void setTokens(vector<string> tokens);
    vector<string> getTokens();

    vector<int> parse();

    static void ensureIntValid(string val);
};