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

TEST(Parser, parseSet)
{
    Parser p;
    vector<string> tokens = {"set", "%A", "123"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({5, 3, -1, 0, 8, 123}));
}

TEST(Parser, parsePushExc)
{
    Parser p;
    vector<string> tokens = {"push"};
    p.setTokens(tokens);

    ASSERT_THROW(p.parse(), runtime_error);
}

TEST(Parser, parseSetExc)
{
    Parser p;
    vector<string> tokens = {"set", "12", "%B"};
    p.setTokens(tokens);

    ASSERT_THROW(p.parse(), runtime_error);

    p.setTokens({"set", "%B", "-123"});
    ASSERT_NO_THROW(p.parse());
}

TEST(Parser, parseAdd)
{
    Parser p;
    vector<string> tokens = {"add"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 4, 8}));
}

TEST(Parser, parseSub)
{
    Parser p;
    vector<string> tokens = {"sub"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 5, 8}));
}

TEST(Parser, parseMul)
{
    Parser p;
    vector<string> tokens = {"mul"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 6, 8}));
}

TEST(Parser, parseDiv)
{
    Parser p;
    vector<string> tokens = {"div"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 7, 8}));
}

TEST(Parser, parseStop)
{
    Parser p;
    vector<string> tokens = {"stop"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 8, 8}));
}

TEST(Parser, multiInstruction)
{
    Parser p;
    vector<string> tokens = { "push", "12", "pop", "%A" };
    p.setTokens(tokens);

    EXPECT_NO_THROW(p.parse());
}

TEST(Parser, inInstruction)
{
    Parser p;
    vector<string> tokens = {"in", "%A"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 9, -1, 8}));
}

TEST(Parser, outInstruction)
{
    Parser p;
    vector<string> tokens = {"out", "%A"};
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 10, -1, 8}));
}

TEST(Parser, outlInstruction)
{
    Parser p;
    vector<string> tokens = { "outl" };
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({-1, 11, 8}));
}

TEST(Parser, parseMark)
{
    Parser p;
    vector<string> tokens = { "mark:" };
    p.setTokens(tokens);

    auto res = p.parse();
    ASSERT_EQ(res, vector<int>({ -1, 19, 8 }));
}

TEST(Parser, parseJump)
{
    Parser p;
    string code = 
    "jump here "
    "push 13 "
    "pop %A "
    "out %A "
    "outl "
    "here: "
    "push 12 "
    "pop %A "
    "out %A "
    "outl ";

    Lexer l;
    l.setInput(code);
    vector<string> tokens = l.getTokens();

    p.setTokens(tokens);

    auto res = p.parse();
    vector<int> expected = { 19, 12, 9, 1, 0, 2, -1, 10, -1, 11, 19, 1, 1, 2, -1, 10, -1, 11, 8, 13, 12 };

    EXPECT_EQ(res, expected);
}

TEST(Parser, parseCmp)
{
    Parser p;
    p.setTokens({"cmp", "1", "1"});

    vector<int> res;
    EXPECT_NO_THROW(res = p.parse());

    vector<int> expected = { 5, 20, 0, 1, 8, 1, 1 };
    EXPECT_EQ(res, expected);
}

TEST(Parser, parseJe)
{
    string code = "cmp 1 1 je here stop here: set %A 228";
    Lexer l;
    l.setInput(code);

    Parser p;
    p.setTokens(l.getTokens());

    vector<int> res;
    EXPECT_NO_THROW(res = p.parse());
    EXPECT_EQ(res, vector<int>({ 12, 20, 0, 1, 13, 6, 8, 19, 3, -1, 2, 8, 1, 1, 228 }));
}

TEST(Parser, parseJl)
{
    string code = "cmp 1 1 jl here stop here: set %A 228";
    Lexer l;
    l.setInput(code);

    Parser p;
    p.setTokens(l.getTokens());

    vector<int> res;
    EXPECT_NO_THROW(res = p.parse());
    EXPECT_EQ(res, vector<int>({ 12, 20, 0, 1, 14, 6, 8, 19, 3, -1, 2, 8, 1, 1, 228 }));
}

TEST(Parser, parseJr)
{
    string code = "cmp 1 1 jr here stop here: set %A 228";
    Lexer l;
    l.setInput(code);

    Parser p;
    p.setTokens(l.getTokens());

    vector<int> res;
    EXPECT_NO_THROW(res = p.parse());
    EXPECT_EQ(res, vector<int>({ 12, 20, 0, 1, 15, 6, 8, 19, 3, -1, 2, 8, 1, 1, 228 }));
}

TEST(Parser, parseJle)
{
    string code = "cmp 1 1 jle here stop here: set %A 228";
    Lexer l;
    l.setInput(code);

    Parser p;
    p.setTokens(l.getTokens());

    vector<int> res;
    EXPECT_NO_THROW(res = p.parse());
    EXPECT_EQ(res, vector<int>({ 12, 20, 0, 1, 16, 6, 8, 19, 3, -1, 2, 8, 1, 1, 228 }));
}

TEST(Parser, parseJre)
{
    string code = "cmp 1 1 jre here stop here: set %A 228";
    Lexer l;
    l.setInput(code);

    Parser p;
    p.setTokens(l.getTokens());

    vector<int> res;
    EXPECT_NO_THROW(res = p.parse());
    EXPECT_EQ(res, vector<int>({ 12, 20, 0, 1, 17, 6, 8, 19, 3, -1, 2, 8, 1, 1, 228 }));
}

TEST(Parser, parseJne)
{
    string code = "cmp 1 1 jne here stop here: set %A 228";
    Lexer l;
    l.setInput(code);

    Parser p;
    p.setTokens(l.getTokens());

    vector<int> res;
    EXPECT_NO_THROW(res = p.parse());
    EXPECT_EQ(res, vector<int>({ 12, 20, 0, 1, 18, 6, 8, 19, 3, -1, 2, 8, 1, 1, 228 }));
}

TEST(Parser, firstEmpty)
{
    string code = "\n set %A 12 out %A outl";
    Lexer l;
    l.setInput(code);

    vector<string> tokens;
    ASSERT_NO_THROW(tokens = l.getTokens());

    Parser p;
    p.setTokens(tokens);
    vector<int> bytes;
    ASSERT_NO_THROW(bytes = p.parse());
}