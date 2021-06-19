#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

#include "Lexer.h"

using namespace std;

class FileReader
{
private:
    static vector<string> splitOnStrBytes(string toSplit);
public:
    static string readAsText(string path);
    static vector<int> readAsBytes(string path);
};