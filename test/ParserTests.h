#include "gtest/gtest.h"
#include "Parser.h"

TEST(Parser, Parser1)
{
    vector<string> tokens({"token", "token"});
    Parser p(tokens);   
    ASSERT_EQ(p.getTokens(), tokens);
}

TEST(Parser, Parser2)
{
    Parser p;
    ASSERT_EQ(p.getTokens(), vector<string>());
}

TEST(Parser, getSetTokens)
{
    Parser p;
    vector<string> tokens({"token", "token"});
    p.setTokens(tokens);
    ASSERT_EQ(p.getTokens(), tokens);
}

TEST(Parser, parse1)
{
    Parser p;
    p.setTokens({});
    auto res = p.parse();

    ASSERT_EQ(res, vector<int>({-1, 8}));
}

TEST(Parser, parsePush)
{
    Parser p;
    vector<string> tokens = {"push", "1337"};
    p.setTokens(tokens);
    
    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({4, 1, 0, 8, 1337}));
}

TEST(Parser, parsePop1)
{
    Parser p;
    vector<string> tokens = {"pop", "%A"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 2, -1, 8}));
}

TEST(Parser, parsePop2)
{
    Parser p;
    vector<string> tokens = {"pop", "123"};
    p.setTokens(tokens);

    ASSERT_THROW(p.parse(), runtime_error);
}

TEST(Parse, parseSet)
{
    Parser p;
    vector<string> tokens = {"set", "%A", "123"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({5, 3, -1, 0, 8, 123}));
}

TEST(Parse, parsePushExc)
{
    Parser p;
    vector<string> tokens = {"push"};
    p.setTokens(tokens);

    ASSERT_THROW(p.parse(), runtime_error);
}

TEST(Parse, parseSetExc)
{
    Parser p;
    vector<string> tokens = {"set", "12", "%B"};
    p.setTokens(tokens);

    ASSERT_THROW(p.parse(), runtime_error);

    p.setTokens({"set", "%B", "-123"});
    ASSERT_NO_THROW(p.parse());
}

TEST(Parse, parseAdd)
{
    Parser p;
    vector<string> tokens = {"add"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 4, 8}));
}

TEST(Parse, parseSub)
{
    Parser p;
    vector<string> tokens = {"sub"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 5, 8}));
}

TEST(Parse, parseMul)
{
    Parser p;
    vector<string> tokens = {"mul"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 6, 8}));
}

TEST(Parse, parseDiv)
{
    Parser p;
    vector<string> tokens = {"div"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 7, 8}));
}

TEST(Parse, parseStop)
{
    Parser p;
    vector<string> tokens = {"stop"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 8, 8}));
}