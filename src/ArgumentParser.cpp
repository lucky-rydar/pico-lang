#include "ArgumentParser.h"

bool ArgumentParser::isValue(string token)
{
    regex val("([0-9]+)");
    return regex_match(token, val);
}

bool ArgumentParser::isRegister(string token)
{
    regex reg("(\\%\\w)");
    return regex_match(token, reg);
}