#include "gtest/gtest.h"
#include "FileWriter.h"

TEST(FileWriter, checkWrite)
{
    vector<int> bytes({1, 2, 3});
    string filename = "a.ple";
    FileWriter::writeBytes(filename, bytes);
    
    ASSERT_EQ(FileReader::readAsBytes(filename), bytes);

    remove(filename.c_str());
}