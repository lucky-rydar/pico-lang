#include "Bytecode.h"

vector<int> Bytecode::getAll()
{
    vector<int> res;
    
    res.insert(res.end(), metaData.begin(), metaData.end());
    res.insert(res.end(), opCodes.begin(), opCodes.end());
    res.insert(res.end(), staticMem.begin(), staticMem.end());
    
    return res;
}