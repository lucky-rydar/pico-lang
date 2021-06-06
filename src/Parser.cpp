#include "Parser.h"

Parser::Parser()
{
    this->tokens = {};
}

Parser::Parser(vector<string> tokens)
{
    this->tokens = tokens;
}

void Parser::setTokens(vector<string> tokens)
{
    this->tokens = tokens;
}

vector<string> Parser::getTokens()
{
    return this->tokens;
}

vector<Instruction> Parser::parse()
{
    vector<Instruction> res;

    return res;
}