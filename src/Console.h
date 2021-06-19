#pragma once
#include <functional>
#include <stdexcept>
#include <vector>
#include <string>
#include <map>

#include "FileReader.h"
#include "FileWriter.h"
#include "Executor.h"
#include "Parser.h"

using namespace std;

class Console
{
private:
    map<string, function<void(vector<string>)>> commands;
public:
    Console();

    void process(vector<string> command);

private:
    void compile(vector<string> params);
    void run(vector<string> params);
};