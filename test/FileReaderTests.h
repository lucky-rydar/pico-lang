#include "gtest/gtest.h"
#include "FileReader.h"

TEST(FileReader, readAsText)
{
    string filename = "hello";
    string text = "Hello world";
    
    ofstream f(filename);
    f << text << endl;
    f.close();

    ASSERT_NO_THROW(FileReader::readAsText(filename));
    

    regex mustBeLike(text + "\\s*");
    auto res = regex_match(FileReader::readAsText(filename), mustBeLike);
    ASSERT_TRUE(res);

    remove(filename.c_str());
}

TEST(FileReader, readAsBytes)
{
    string filename = "hello";
    string text = "123 -12 44";
    vector<int> mustBe = {123, -12, 44};

    ofstream f(filename);
    f << text << endl;
    f.close();

    ASSERT_NO_THROW(FileReader::readAsBytes(filename));
    
    ASSERT_EQ(FileReader::readAsBytes(filename), mustBe);

    remove(filename.c_str());
}

TEST(FileReader, invalidBytesInFile)
{
    string filename = "src.pls";
    string text = "123 ghg 12";
    
    ofstream f(filename);
    f << text << endl;
    f.close();

    EXPECT_THROW(FileReader::readAsBytes(filename), runtime_error);

    remove(filename.c_str());
}