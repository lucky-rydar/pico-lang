#pragma once
#include <map>
#include <regex>
#include <vector>
#include <iostream>
#include <functional>

#include "ArgumentParser.h"

using namespace std;

// this class will be used to rewrite 
// tokens as it will be comfortable for parser
// For example, for *push* instruction will be generated push_reg and push_val
// because *push* can use register and just value 

class TokenFormatter
{
private:
    typedef ArgumentParser ArgPars;
    vector<string> sourceTokens;
    vector<string> resTokens;
    map<string, function<void(size_t)>> formatters;
    map<string, int> tokenSize;

    void formatPush(size_t index);
    void formatSet(size_t index);
public:
    TokenFormatter();
    TokenFormatter(vector<string> sourceTokens);

    void setSource(vector<string> sourceTokens);

    vector<string> format();
};
