#pragma once
#include <vector>

using namespace std;

class Bytecode
{
public:
    vector<int> metaData;
    vector<int> opCodes;
    vector<int> staticMem;
};