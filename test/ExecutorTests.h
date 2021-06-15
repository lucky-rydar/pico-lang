#include "Executor.h"

TEST(Executor, getState)
{
    Executor e;
    
    ASSERT_EQ(e.getBytes(), vector<int>());

    e.setBytes({1, 2, 3});
    ASSERT_EQ(e.getBytes(), vector<int>({1, 2, 3}));
}

TEST(Executor, execPush)
{
    Executor e;
    e.setBytes(vector<int>({4, 1, 0, 8, 1337})); // push 1337

    e.execute();

    auto state = e.getState();
    state.popVal(Instruction::A);
    ASSERT_EQ(state.getRegVal(Instruction::A), 1337);
}

TEST(Executor, execPop)
{
    Executor e;
    e.setBytes(vector<int>({6, 1, 0, 2, -1, 8, 1337})); 

    e.execute();

    auto state = e.getState();

    ASSERT_EQ(state.getRegVal(Instruction::A), 1337);
}

TEST(Executor, execSet)
{
    Executor e;
    e.setBytes(vector<int>({5, 3, -1, 0, 8, 123}));
    e.execute();

    auto state = e.getState();
    ASSERT_EQ(state.getRegVal(Instruction::A), 123);
}

TEST(Executor, execAdd)
{
    Executor e;

    // push 2 push 2 add pop %A
    e.setBytes(vector<int>({9, 1, 0, 1, 1, 4, 2, -1, 8, 2, 2}));

    e.execute();

    auto state = e.getState();
    ASSERT_EQ(state.getRegVal(Instruction::A), 4);
}

TEST(Executor, execSub)
{
    Executor e;

    // push 2 push 2 sub pop %A
    e.setBytes(vector<int>({9, 1, 0, 1, 1, 5, 2, -1, 8, 2, 2}));

    e.execute();

    auto state = e.getState();
    ASSERT_EQ(state.getRegVal(Instruction::A), 0);
}