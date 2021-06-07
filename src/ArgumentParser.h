#pragma once
#include <regex>
#include <string>

using namespace std;

class ArgumentParser
{
private:
    
public:
    static bool isValue(string token);
    static bool isRegister(string token);
};
