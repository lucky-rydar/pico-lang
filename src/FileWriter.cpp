#include "FileWriter.h"

void FileWriter::writeBytes(string dst, vector<int> bytes)
{
    ofstream file(dst);

    for(auto byte : bytes)
    {
        file << byte << " ";
    }

    file.close();
}