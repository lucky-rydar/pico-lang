#include "gtest/gtest.h"
#include "LexerTests.h"
#include "ParserTests.h"
#include "ArgumentParserTests.h"
#include "ExecutorTests.h"
#include "ConsoleTests.h"
#include "FileReaderTests.h"
#include "FileWriterTests.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}