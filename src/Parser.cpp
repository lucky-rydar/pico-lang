#include "Parser.h"

Parser::Parser()
{
    this->tokens = {};

    parserByToken["push"] = bind(&Parser::parsePush, this, std::placeholders::_1, std::placeholders::_2);
    parserByToken["pop"] = bind(&Parser::parsePop, this, std::placeholders::_1, std::placeholders::_2);
    parserByToken["set"] = bind(&Parser::parseSet, this, std::placeholders::_1, std::placeholders::_2);

    parserByToken["add"] = bind(&Parser::parseAdd, this, std::placeholders::_1, std::placeholders::_2);
    parserByToken["sub"] = bind(&Parser::parseSub, this, std::placeholders::_1, std::placeholders::_2);
    parserByToken["mul"] = bind(&Parser::parseMul, this, std::placeholders::_1, std::placeholders::_2);
    parserByToken["div"] = bind(&Parser::parseDiv, this, std::placeholders::_1, std::placeholders::_2);

    parserByToken["stop"] = bind(&Parser::parseStop, this, std::placeholders::_1, std::placeholders::_2);
}

Parser::Parser(vector<string> tokens) : Parser()
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

void parsePush(vector<Instruction>& ins, int &index)
{

}

void parsePop(vector<Instruction>& ins, int &index)
{
    
}

void parseSet(vector<Instruction>& ins, int &index)
{
    
}

void parseAdd(vector<Instruction>& ins, int &index)
{
    
}

void parseSub(vector<Instruction>& ins, int &index)
{
    
}

void parseMul(vector<Instruction>& ins, int &index)
{
    
}

void parseDiv(vector<Instruction>& ins, int &index)
{
    
}

void parseStop(vector<Instruction>& ins, int &index)
{
    
}