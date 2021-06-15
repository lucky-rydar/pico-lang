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
    cout << state.getRegVal(Instruction::A) << endl;


    ASSERT_EQ(state.getRegVal(Instruction::A), 1337);
}