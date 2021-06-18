#pragma once
#include <functional>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Console
{
private:
    map<string, function<void(vector<string>)>> commands;
public:
    Console();

    void getLine();
};