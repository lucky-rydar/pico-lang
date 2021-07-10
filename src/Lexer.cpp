#include "Lexer.h"

Lexer::Lexer()
{
    this->delimiter = "(?:[\n\\s\r\t]*\\,[\n\\s\r\t]*)|(?:[\n\\s\r\t]+)"; 
}

Lexer::Lexer(string input) : Lexer()
{
    this->input = input;
}

Lexer::Lexer(string input, string delimiter)
{
    this->input = input;
    this->delimiter = delimiter;
}

void Lexer::setInput(string input)
{
    this->input = input;
}

string Lexer::getInput()
{
    return this->input;
}

void Lexer::setDelimiter(string delimiter)
{
    this->delimiter = delimiter;
}

string Lexer::getDelimiter()
{
    return this->delimiter;
}

vector<string> Lexer::getTokens()
{
    if(input == "")
        return {};
    
    int notSpaceIdx = 0;
    for( ; input[notSpaceIdx] == ' ' || input[notSpaceIdx] == '\n' || 
            input[notSpaceIdx] == '\r' || input[notSpaceIdx] == '\t'; notSpaceIdx++);

    string cut(input.begin() + notSpaceIdx, input.end());

    regex delimiterRegex(delimiter);
    vector<string> res;
    
    copy(sregex_token_iterator(cut.begin(), cut.end(), delimiterRegex, -1),
        sregex_token_iterator(),
        back_inserter(res));
    
    return res;
}