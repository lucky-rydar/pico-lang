#pragma once
#include <map>
#include <vector>
#include <exception>

#include "State.h"
#include "Parser.h"
#include "Metadata.h"

using namespace std;

class Executor
{
private:
    vector<int> bytes;
    int ip; // index of current instruction

    State state;
    Metadata metadata;
    map<Instruction, function<void()>> instructions;
public:
    Executor();
    Executor(vector<int> bytes);

    void setBytes(vector<int> bytes);
    vector<int> getBytes();

    void execute();

    void readMetadata();
    State getState();
private:
    void push();
    void pop();
    void set();

    void add();
    void sub();
    void mul();
    void div();

    void in();
    void out();
    void outl();
};