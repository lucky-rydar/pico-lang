#pragma once
#include <vector>
#include <iostream>

using namespace std;

// this class will be used to rewrite 
// tokens as it will be comfortable for parser
// For example, for *push* instruction will be generated push_reg and push_val
// because *push* can use register and just value 

class TokenFormatter
{
private:
    vector<string> sourceTokens;
public:
    TokenFormatter();
    TokenFormatter(vector<string> sourceTokens);

    void setSource(vector<string> sourceTokens);

    vector<string> format();
};
