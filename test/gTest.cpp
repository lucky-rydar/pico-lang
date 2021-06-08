#include "gtest/gtest.h"
#include "LexerTests.h"
#include "ParserTests.h"
#include "TokenFormatterTests.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}