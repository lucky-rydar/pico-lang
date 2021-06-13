#include "Parser.h"

Parser::Parser()
{
    this->tokens = {};

    parserByToken["push"] = bind(&Parser::parsePush, this, std::placeholders::_1);
    parserByToken["pop"] = bind(&Parser::parsePop, this, std::placeholders::_1);
    parserByToken["set"] = bind(&Parser::parseSet, this, std::placeholders::_1);

    parserByToken["add"] = bind(&Parser::parseAdd, this, std::placeholders::_1);
    parserByToken["sub"] = bind(&Parser::parseSub, this, std::placeholders::_1);
    parserByToken["mul"] = bind(&Parser::parseMul, this, std::placeholders::_1);
    parserByToken["div"] = bind(&Parser::parseDiv, this, std::placeholders::_1);

    parserByToken["stop"] = bind(&Parser::parseStop, this, std::placeholders::_1);

    registerByToken["%A"] = Instruction::A;
    registerByToken["%B"] = Instruction::B;
    registerByToken["%C"] = Instruction::C;
    registerByToken["%D"] = Instruction::D;
    registerByToken["%E"] = Instruction::E;
    registerByToken["%F"] = Instruction::F;
    registerByToken["%G"] = Instruction::G;
    registerByToken["%H"] = Instruction::H;
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

vector<int> Parser::parse()
{
    for(int i = 0; i < tokens.size(); i++)
    {
        if(parserByToken.find(tokens[i]) != parserByToken.end())
        {
            try
            {
                parserByToken[tokens[i]](i);
            }
            catch(runtime_error)
            {
                throw;
            }
        }
        else
        {
            throw runtime_error(string("token '") + tokens[i] + "' is not expected");
        }
    }

    bytecode.opCodes.push_back((int)Instruction::Stop);

    processMetadata();

    return bytecode.getAll();
}

void Parser::parsePush(int &index)
{ 
    if(index + 1 >= tokens.size())
        throw runtime_error("out of range"); 

    string ins = tokens[index];
    string arg = tokens[index+1];
    
    bytecode.opCodes.push_back((int)Instruction::Push);

    if(ArgPars::isRegister(arg))
    {
        if(registerByToken.find(arg) == registerByToken.end())
            throw runtime_error("there is no register '" + arg + "'");

        bytecode.opCodes.push_back((int)registerByToken[arg]);
    }
    else if(ArgPars::isValue(arg))
    {
        ensureIntValid(arg);
        int value = stoi(arg);
        
        bytecode.staticMem.push_back(value);
        bytecode.opCodes.push_back(bytecode.staticMem.size() - 1);
    }
    else
    {
        throw runtime_error("unknown argument '" + arg + "'");
    }

    index += 2;
}

void Parser::parsePop(int &index)
{
    if(index + 1 >= tokens.size())
        throw runtime_error("out of range"); 
    
    string ins = tokens[index];
    string arg = tokens[index+1];

    bytecode.opCodes.push_back((int)Instruction::Pop);

    if(ArgPars::isRegister(arg))
    {
        if(registerByToken.find(arg) == registerByToken.end())
            throw runtime_error("there is no register '" + arg + "'");

        bytecode.opCodes.push_back((int)registerByToken[arg]);
    }
    else
    {
        throw runtime_error("argument '" + arg + "' is not register");
    }

    index += 1;
}

void Parser::parseSet(int &index)
{
    if(index + 2 >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[index];
    bytecode.opCodes.push_back((int)Instruction::Set);

    vector<string> args = {tokens[index + 1], tokens[index + 2]};
    
    for(int i = 0; i < args.size(); i++)
    {
        if(i == 0)
        {
            if(!ArgPars::isRegister(args[i]))
                throw runtime_error("first argument is not register: '" + args[i] + "'");
        }

        if(ArgPars::isRegister(args[i]))
        {
            if(registerByToken.find(args[i]) == registerByToken.end())
                throw runtime_error("there is no register '" + args[i] + "'");

            bytecode.opCodes.push_back((int)registerByToken[args[i]]);
        }
        else if(ArgPars::isValue(args[i]))
        {
            ensureIntValid(args[i]);
            int value = stoi(args[i]);

            bytecode.staticMem.push_back(value);
            bytecode.opCodes.push_back(bytecode.staticMem.size() - 1);
        }
        else
        {
            throw runtime_error("unknown argument '" + args[i] + "'");
        }
    }

    index += 3;
}

void Parser::parseAdd(int &index)
{
    if(index >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[index];
    bytecode.opCodes.push_back((int)Instruction::Add);

    index += 1;
}

void Parser::parseSub(int &index)
{
    if(index >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[index];
    bytecode.opCodes.push_back((int)Instruction::Sub);

    index += 1;
}

void Parser::parseMul(int &index)
{
    if(index >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[index];
    bytecode.opCodes.push_back((int)Instruction::Mul);

    index += 1;
}

void Parser::parseDiv(int &index)
{
    if(index >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[index];
    bytecode.opCodes.push_back((int)Instruction::Div);

    index += 1;
}

void Parser::parseStop(int &index)
{
    if(index >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[index];
    bytecode.opCodes.push_back((int)Instruction::Stop);

    index += 1;
}

void Parser::ensureIntValid(string val)
{
    try
    {
        stoi(val);
    }
    catch(exception)
    {
        throw runtime_error("value '" + val + "' is invalid");
    }   
}

void Parser::processMetadata()
{
    if(bytecode.staticMem.size() > 0)
        bytecode.metaData.push_back(bytecode.opCodes.size() + 1);
    else
        // -1 means that static memory is not allocated
        bytecode.metaData.push_back(-1);
}