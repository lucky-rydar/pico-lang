#include <iostream>
#include "Console.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        cout << "Not enough arguments" << endl;
        return -1;
    }

    vector<string> command;
    for(int i = 1; i < argc; i++)
        command.push_back(string(argv[i]));

    try
    {
        Console c;
        c.process(command);
    }
    catch(runtime_error re)
    {
        cout << "Something is wrong: " << re.what() << endl;
        return -1;
    }

    return 0;
}