#include "gtest/gtest.h"
#include "TokenFormatter.h"

TEST(TokenFormatter, TokenFormatter1)
{
    TokenFormatter tf;
    ASSERT_EQ(tf.format(), vector<string>());
}

TEST(TokenFormatter, format_push)
{
    TokenFormatter tf;
    ASSERT_NO_THROW(tf.format());
    
    vector<string> tokens1 = {"push", "123"};
    vector<string> tokens2 = {"push", "%A"};

    tf.setSource(tokens1);
    ASSERT_EQ(tf.format(), vector<string>({"push_val", "123"}));

    tf.setSource(tokens2);
    ASSERT_EQ(tf.format(), vector<string>({"push_reg", "%A"}));
}

TEST(TokenFormatter, format_set)
{
    TokenFormatter tf;
    ASSERT_NO_THROW(tf.format());
    
    vector<string> tokens1 = {"set", "%A", "123"};
    vector<string> tokens2 = {"set", "%A", "%B"};

    tf.setSource(tokens1);
    ASSERT_EQ(tf.format(), vector<string>({"set_val", "%A", "123"}));
    ASSERT_EQ(tf.format(), vector<string>({"set_val", "%A", "123"}));

    tf.setSource(tokens2);
    ASSERT_EQ(tf.format(), vector<string>({"set_reg", "%A", "%B"}));
}

TEST(TokenFormatter, format_exception)
{
    TokenFormatter tf;
    
    vector<string> tokens = {"push"};
    tf.setSource(tokens);

    try
    {
        tf.format();
    }
    catch(std::exception e)
    {
        cout << "the error: " << e.what() << endl;
    }

    ASSERT_NO_THROW(tf.format());
    ASSERT_EQ(tf.format(), vector<string>({"push"}));
}