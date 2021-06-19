#include "Console.h"

Console::Console()
{
    commands["compile"] = std::bind(&Console::compile, this, std::placeholders::_1);
    commands["run"] = std::bind(&Console::run, this, std::placeholders::_1);
}

void Console::process(vector<string> command)
{
    if(command.size() < 1)
        throw runtime_error("command is not specified");
    if(command[0] == "")
        throw runtime_error("empty command");

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
    if(params.size() == 0)
        throw runtime_error("too few arguments for command 'compile'");

    string source = params[0];
    string executable;
    
    if(params.size() == 1)
        executable = "a.ple";
    else if(params.size() == 2)
        executable = params[1];
    
    string code;
    try
    {
        code = FileReader::readAsText(source);    
    }
    catch(runtime_error)
    {
        throw;
    }
    
    Lexer l(code);
    auto tokens = l.getTokens();
    
    Parser p;
    p.setTokens(tokens);
    auto bytes = p.parse();
    
    FileWriter::writeBytes(executable, bytes);
}

void Console::run(vector<string> params)
{
    if(params.size() == 0)
        throw runtime_error("too few arguments for command 'compile'");
    
    string executable = params[0];

    vector<int> bytes;
    try
    {
        bytes = FileReader::readAsBytes(executable);    
    }
    catch(runtime_error)
    {
        throw;
    }
    
    Executor e;
    e.setBytes(bytes);

    try
    {
        e.execute();
    }
    catch(runtime_error)
    {
        throw;
    }
}