#pragma once
#include <vector>

using namespace std;

class Executor
{
private:
    vector<int> bytes;
    int ip; // index of current instruction

    // TODO: add state class object to store registers data and stack

public:
    Executor();
    Executor(vector<int> bytes);

    void setBytes(vector<int> bytes);
    vector<int> getBytes();

    void execute();

private:
    //TODO: here add all instructions functions
};