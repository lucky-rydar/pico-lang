#include "gtest/gtest.h"
#include "Console.h"

TEST(Console, processExc)
{
    Console c;
    auto command1 = vector<string>({"compile"});
    EXPECT_NO_THROW(c.process(command1));
    
    auto command2 = vector<string>({"hello"});
    EXPECT_THROW(c.process(command2), std::runtime_error);
}