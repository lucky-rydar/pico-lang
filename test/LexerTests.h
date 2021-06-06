#include "gtest/gtest.h"
#include "Lexer.h"

TEST(Lexer, Lexer1)
{
    Lexer l;
    ASSERT_EQ(l.getDelimiter(), "(?:[\n\\s]*\\,[\n\\s]*)|(?:[\n\\s]+)");
    ASSERT_EQ(l.getInput(), "");
}

TEST(Lexer, Lexer2)
{
    Lexer l("secret input");
    ASSERT_EQ(l.getInput(), "secret input");
    ASSERT_EQ(l.getDelimiter(), "(?:[\n\\s]*\\,[\n\\s]*)|(?:[\n\\s]+)");
}

TEST(Lexer, Lexer3)
{
    Lexer l("input", "delimeter");
    ASSERT_EQ(l.getInput(), "input");
    ASSERT_EQ(l.getDelimiter(), "delimeter");
}

TEST(Lexer, parse1)
{
    string text = "hello, I am   pico-lang";
    vector<string> expected({"hello", "I", "am", "pico-lang"});
    Lexer l(text);
    ASSERT_EQ(l.parse(), expected);
}

TEST(Lexer, parse2)
{
    string text = "hello, , pico-lang";
    vector<string> expected({"hello", "", "pico-lang"});
    Lexer l(text);
    ASSERT_EQ(l.parse(), expected);
}

TEST(Lexer, parse3)
{
    string text = "";
    vector<string> expected({});
    Lexer l(text);
    
    ASSERT_EQ(l.parse(), expected);
}

TEST(Lexer, parse4)
{
    string text = "Hello,\nI am\npico-lang";
    vector<string> expected({"Hello", "I", "am", "pico-lang"});
    Lexer l(text);
    ASSERT_EQ(l.parse(), expected);
}