#include "Console.h"

Console::Console()
{
    commands["compile"] = std::bind(&Console::compile, this, std::placeholders::_1);
    commands["run"] = std::bind(&Console::run, this, std::placeholders::_1);
}

void Console::process(vector<string> command)
{
    if(commands.find(command[0]) == commands.end())
    {
        throw std::runtime_error(string("there is no such command as '" + command[0] + "'"));
    }
    else
    {
        if(command.size() >= 2)
            commands[command[0]](vector<string>(command.begin() + 1, command.end()));
    }
}

void Console::compile(vector<string> params)
{

}

void Console::run(vector<string> params)
{

}