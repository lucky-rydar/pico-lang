#include "FileReader.h"

string FileReader::readAsText(string path)
{
    if(!filesystem::exists(filesystem::path(path)))
        throw runtime_error("file does not exist");

    ifstream file;
    file.open(path);

    string res;
    string buff;
    while(!file.eof())
    {
        std::getline(file, buff);
        res += buff;
    }
    file.close();

    return res;
}

vector<int> FileReader::readAsBytes(string path)
{
    string text = readAsText(path);
    
    auto splitted = splitOnStrBytes(text);
    vector<int> res;

    for(auto str : splitted)
    {
        try
        {
            res.push_back(stoi(str));
        }
        catch(exception)
        {
            throw runtime_error("file if not valid");
        }
    }

    return res;
}

vector<string> FileReader::splitOnStrBytes(string toSplit)
{
    Lexer l(toSplit);
    l.setDelimiter("\\s");

    return l.getTokens();
}