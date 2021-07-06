#include "Parser.h"

Parser::Parser()
{
    this->tokens = {};

    parserByToken["push"] = bind(&Parser::parsePush, this);
    parserByToken["pop"] = bind(&Parser::parsePop, this);
    parserByToken["set"] = bind(&Parser::parseSet, this);

    parserByToken["add"] = bind(&Parser::parseAdd, this);
    parserByToken["sub"] = bind(&Parser::parseSub, this);
    parserByToken["mul"] = bind(&Parser::parseMul, this);
    parserByToken["div"] = bind(&Parser::parseDiv, this);

    parserByToken["stop"] = bind(&Parser::parseStop, this);

    parserByToken["in"] = bind(&Parser::parseIn, this);
    parserByToken["out"] = bind(&Parser::parseOut, this);
    parserByToken["outl"] = bind(&Parser::parseOutl, this);

    parserByToken["\\w+\\:"] = bind(&Parser::parseMark, this);
    parserByToken["pass"] = bind(&Parser::parsePass, this);
    parserByToken["jump"] = bind(&Parser::parseJump, this);
    parserByToken["cmp"] = bind(&Parser::parseCmp, this);

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
    processMarks();

    for(ct = 0; ct < tokens.size();)
    {
        auto parser = parserByToken.begin();
        for(; parser != parserByToken.end(); parser++)
        {
            regex reInstr(parser->first);
            if(regex_match(tokens[ct], reInstr))
            {
                try
                {
                    parserByToken.at(parser->first)();
                    break;
                }
                catch(runtime_error)
                {
                    throw;
                }
            }
        }
        
        if(parser == parserByToken.end())
            throw runtime_error(string("token '") + tokens[ct] + "' is not expected");
    }

    bytecode.opCodes.push_back((int)Instruction::Stop);

    processMetadata();

    return bytecode.getAll();
}

void Parser::parsePush()
{ 
    if(ct + 1 >= tokens.size())
        throw runtime_error("out of range"); 

    string ins = tokens[ct];
    string arg = tokens[ct+1];
    
    bytecode.opCodes.push_back((int)Instruction::Push);

    parseValRegArg(arg);

    ct += 2;
}

void Parser::parsePop()
{
    if(ct + 1 >= tokens.size())
        throw runtime_error("out of range"); 
    
    string ins = tokens[ct];
    string arg = tokens[ct+1];

    bytecode.opCodes.push_back((int)Instruction::Pop);

    parseRegArg(arg);

    ct += 2;
}

void Parser::parseSet()
{
    if(ct + 2 >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    bytecode.opCodes.push_back((int)Instruction::Set);

    string arg1 = tokens[ct + 1];
    string arg2 = tokens[ct + 2];

    parseRegArg(arg1);
    parseValRegArg(arg2);

    ct += 3;
}

void Parser::parseAdd()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    bytecode.opCodes.push_back((int)Instruction::Add);

    ct += 1;
}

void Parser::parseSub()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    bytecode.opCodes.push_back((int)Instruction::Sub);

    ct += 1;
}

void Parser::parseMul()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    bytecode.opCodes.push_back((int)Instruction::Mul);

    ct += 1;
}

void Parser::parseDiv()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    bytecode.opCodes.push_back((int)Instruction::Div);

    ct += 1;
}

void Parser::parseStop()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    bytecode.opCodes.push_back((int)Instruction::Stop);

    ct += 1;
}

void Parser::parseIn()
{
    if(ct + 1 >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    string arg = tokens[ct+1];

    bytecode.opCodes.push_back((int)Instruction::In);

    parseRegArg(arg);

    ct += 2;
}

void Parser::parseOut()
{
    if(ct + 1 >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    string arg = tokens[ct+1];

    bytecode.opCodes.push_back((int)Instruction::Out);

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

    ct += 2;
}

void Parser::parseOutl()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];
    bytecode.opCodes.push_back((int)Instruction::Outl);

    ct += 1;
}

void Parser::parseMark()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");
    
    string ins = tokens[ct];

    regex mark_parser("(\\w+)\\:");
    smatch parsed;
    
    if(regex_match(ins, parsed, mark_parser))
    {
        string mark = parsed[1];
        marks[mark] = ct;

        bytecode.opCodes.push_back((int)Instruction::Pass);
    }
    else
        throw runtime_error("mark is not available");

    ct += 1;
}

void Parser::parsePass()
{
    if(ct >= tokens.size())
        throw runtime_error("out of range");

    string ins = tokens[ct];

    bytecode.opCodes.push_back((int)Instruction::Pass);

    ct += 1;
}

void Parser::parseJump()
{
    if(ct + 1 >= tokens.size())
        throw runtime_error("out of range");
    
    string ins = tokens[ct];
    string to_jump = tokens[ct+1];
    
    bytecode.opCodes.push_back((int)Instruction::Jump);

    if(marks.find(to_jump) != marks.end())
    {
        bytecode.opCodes.push_back(marks[to_jump]);
    }
    else
    {
        throw runtime_error("mark '" + to_jump + "' is invalid");
    }
    
    ct += 2;
}

void Parser::parseCmp()
{
    if(ct + 2 >= tokens.size())
        throw runtime_error("out o frange");

    string ins = tokens[ct];
    string arg1 = tokens[ct + 1];
    string arg2 = tokens[ct + 2];

    bytecode.opCodes.push_back((int)Instruction::Cmp);

    parseValRegArg(arg1);
    parseValRegArg(arg2);

    ct += 3;
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

void Parser::processMarks()
{
    for (size_t i = 0; i < tokens.size(); i++)
    {
        smatch parsed;
        if(regex_match(tokens[i], parsed, regex("(\\w+)\\:")))
        {
            marks[parsed[1]] = i;
        }
    }
}

void Parser::parseValRegArg(string arg)
{
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
}

void Parser::parseRegArg(string arg)
{
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
}

void Parser::parseValArg(string arg)
{
    // it can be useless
}