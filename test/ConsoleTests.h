#include "gtest/gtest.h"
#include "Console.h"

TEST(Console, processExc)
{
    Console c;
    auto command1 = vector<string>({"compile"});
    EXPECT_THROW(c.process(command1), runtime_error);
    
    auto command2 = vector<string>({"hello"});
    EXPECT_THROW(c.process(command2), std::runtime_error);
}

TEST(Console, processEmpty)
{
    Console c;
    auto command1 = vector<string>({});
    auto command2 = vector<string>({""});

    ASSERT_THROW(c.process(command1), runtime_error);
    ASSERT_THROW(c.process(command2), runtime_error);
}

TEST(Console, compileTest)
{
    Console c;
    string filename = "test.pl";
    vector<string> command = {"compile", filename};
    
    string code = "push 12 pop %A";
    Lexer l(code);
    Parser p;
    p.setTokens(l.getTokens());
    auto bytes1 = p.parse();
    
    ofstream file(filename);
    file << code;
    file.close();

    c.process(command);

    auto bytes2 = FileReader::readAsBytes("a.ple");

    ASSERT_EQ(bytes1, bytes2);

    remove(filename.c_str());
    remove("a.ple");
}

TEST(Console, runTest)
{
    Console c;
    string filename = "test.pl";
    
    vector<string> commandCompile = {"compile", filename};

    string code = "push 12 pop %A";
    Lexer l(code);
    Parser p;
    p.setTokens(l.getTokens());
    auto bytes1 = p.parse();
    
    ofstream file(filename);
    file << code;
    file.close();

    c.process(commandCompile);

    string execFile = "a.ple";
    vector<string> commandRun = {"run", execFile};
    
    EXPECT_NO_THROW(c.process(commandRun));

    remove("test.pl");
}

TEST(Console, processMultiline)
{
    Console c;
    string sourceFile = "src.pls";
    vector<string> commandCompile = {"compile", sourceFile};

    string code = "push 12\npop %A";

    Lexer l(code);
    Parser p;
    p.setTokens(l.getTokens());
    auto bytes1 = p.parse();
    
    ofstream file(sourceFile);
    file << code;
    file.close();

    c.process(commandCompile);

    string execFile = "a.ple";
    vector<string> commandRun = {"run", execFile};  

    EXPECT_NO_THROW(c.process(commandRun));

    remove(execFile.c_str());
    remove(sourceFile.c_str());
}

TEST(Console, compileTestSizeException)
{
    Console c;

    ASSERT_THROW(c.process(vector<string>({"compile"})), runtime_error);
}

TEST(Console, runTestSizeException)
{
    Console c;

    ASSERT_THROW(c.process(vector<string>({"run"})), runtime_error);
}

TEST(Console, compileTwoParams)
{
    Console c;
    ASSERT_THROW(c.process({"compile", "main.pls", "a.ple"}), runtime_error);   
}