#pragma once
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;

class FileWriter
{
private:
    
public:
    static void writeBytes(string dst, vector<int> bytes);
};