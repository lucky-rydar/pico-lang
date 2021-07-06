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
    e.setBytes(vector<int>({9, 1, 0, 1, 1, 5, 2, -1, 8, 3, 2}));

    e.execute();

    auto state = e.getState();
    ASSERT_EQ(state.getRegVal(Instruction::A), 1);
}

TEST(Executor, execMul)
{
    Executor e;

    // push 2 push 2 mul pop %A
    e.setBytes(vector<int>({9, 1, 0, 1, 1, 6, 2, -1, 8, 3, 2}));

    e.execute();

    auto state = e.getState();
    ASSERT_EQ(state.getRegVal(Instruction::A), 6);
}

TEST(Executor, execDiv)
{
    Executor e;

    // push 2 push 2 div pop %A
    e.setBytes(vector<int>({9, 1, 0, 1, 1, 7, 2, -1, 8, 8, 2}));

    e.execute();

    auto state = e.getState();
    ASSERT_EQ(state.getRegVal(Instruction::A), 4);
}

TEST(Executor, popEmpty)
{
    Executor e;
    
    EXPECT_NO_THROW(e.setBytes({15, 1, 0, 1, 1, 6, 1, 2, 4, 2, -1, 10, -1, 11, 8, 4, 5, 3}));

    ASSERT_NO_THROW(e.execute());

}

TEST(Executor, pass)
{
    Executor e;

    EXPECT_NO_THROW(e.setBytes({-1, 19, 8}));

    EXPECT_NO_THROW(e.execute());
}

TEST(Executor, jump)
{
    Executor e;

    EXPECT_NO_THROW(e.setBytes(vector<int>({ 19, 12, 9, 1, 0, 2, -1, 10, -1, 11, 19, 1, 1, 2, -1, 10, -1, 11, 8, 13, 12 })));

    EXPECT_NO_THROW(e.execute());

    auto stateVal = e.getState().getRegVal(Instruction::A);

    EXPECT_EQ(stateVal, 12);
}