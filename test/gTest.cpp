#define EXPECT_THROW

#include "gtest/gtest.h"
#include "LexerTests.h"
#include "ParserTests.h"
#include "TokenFormatterTests.h"
#include "ArgumentParserTests.h"
#include "ExecutorTests.h"
#include "ConsoleTests.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}