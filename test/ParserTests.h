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