#include "gtest/gtest.h"
#include "ArgumentParser.h"

TEST(ArgumentParser, isValue1)
{
    ASSERT_TRUE(ArgumentParser::isValue("123"));
    ASSERT_TRUE(ArgumentParser::isValue("-123"));
    ASSERT_TRUE(ArgumentParser::isValue("0123"));
    
    ASSERT_FALSE(ArgumentParser::isValue("%A"));
    ASSERT_FALSE(ArgumentParser::isValue("ghg"));
}

TEST(ArgumentParser, isRegister)
{
    ASSERT_TRUE(ArgumentParser::isRegister("%A"));
    ASSERT_TRUE(ArgumentParser::isRegister("%B"));
    ASSERT_TRUE(ArgumentParser::isRegister("%H"));
    
    ASSERT_FALSE(ArgumentParser::isRegister("abc"));
    ASSERT_FALSE(ArgumentParser::isRegister("123"));
}