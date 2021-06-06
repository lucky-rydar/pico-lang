#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

class Lexer
{
private:
    string input;
    string delimiter;
    vector<string> tokens;

public:
    Lexer();
    Lexer(string input);
    Lexer(string input, string delimiter);

    void setInput(string input);
    string getInput();

    void setDelimiter(string delimiter);
    string getDelimiter();

    vector<string> parse();
};