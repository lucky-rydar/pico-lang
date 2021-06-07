#include "TokenFormatter.h"

TokenFormatter::TokenFormatter()
{
    this->sourceTokens = {};

    formatters["push"] = std::bind(&TokenFormatter::formatPush, this, std::placeholders::_1);
    tokenSize["push"] = 2;
    formatters["set"] = std::bind(&TokenFormatter::formatSet, this, std::placeholders::_1);
    tokenSize["set"] = 3;
}

TokenFormatter::TokenFormatter(vector<string> sourceTokens) : TokenFormatter()
{
    setSource(sourceTokens);
}

void TokenFormatter::setSource(vector<string> sourceTokens)
{
    this->sourceTokens = sourceTokens;
    this->resTokens = sourceTokens;
}

vector<string> TokenFormatter::format()
{
    for (size_t i = 0; i < sourceTokens.size();)
    {
        if(formatters.find(sourceTokens[i]) != formatters.end())
        {
            formatters[sourceTokens[i]](i);
            i += tokenSize[sourceTokens[i]];
            
            continue;
        }
        i++;
    }
    
    return resTokens;
}

void TokenFormatter::formatPush(size_t index)
{
    string in, arg; // instruction and argument
    
    try
    {
        in = this->sourceTokens[index];
        arg = this->sourceTokens[index+1];
    }
    catch(std::exception)
    {
        throw std::runtime_error("not enough arguments");
    }

    if(ArgPars::isRegister(arg))
        resTokens[index] = "push_reg";
    if(ArgPars::isValue(arg))
        resTokens[index] = "push_val";
}

void TokenFormatter::formatSet(size_t index)
{
    string in, arg1, arg2;

    try
    {
        in = this->sourceTokens[index];
        arg1 = this->sourceTokens[index+1];
        arg2 = this->sourceTokens[index+2];
    }
    catch(std::exception)
    {
        throw std::runtime_error("not enough arguments");
    }

    if(ArgPars::isRegister(arg2))
        resTokens[index] = "set_reg";
    else if(ArgPars::isValue(arg2))
        resTokens[index] = "set_val";
}