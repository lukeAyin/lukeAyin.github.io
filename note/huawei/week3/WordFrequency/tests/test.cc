#include <gtest/gtest.h>  // googletest header file
//#include <gmock/gmock.h>  // googletest header file

#include "WordFrequency.h"

// 结果字符串输出长度含尾字符长度为11，匹配有效等价类
TEST(WordFrequencyTest, test_two_word_sort_normal)
{
    char* wordString = WordFrequencyFunc("the the is");
    ASSERT_TRUE(wordString != NULL);
    ASSERT_STREQ(wordString, "the 2\nis 1");
}

// 结果字符串输出长度含尾字符长度为15，匹配边界值，有效等价类
TEST(WordFrequencyTest, test_valid_boundary_inner_value_string)
{
    char* wordString = WordFrequencyFunc("aa bb bb cc cc cc");
    ASSERT_TRUE(wordString != NULL);
    ASSERT_STREQ(wordString, "cc 3\nbb 2\naa 1");
}

// 结果字符串输出长度含尾字符长度为16，匹配边界值，有效等价类
TEST(WordFrequencyFuncTest, test_valid_boundary_value_string)
{
    char* wordString = WordFrequencyFunc("aaa bb bb cc cc cc");
    ASSERT_TRUE(wordString != NULL);
    ASSERT_STREQ(wordString, "cc 3\nbb 2\naaa 1");
}

// 结果字符串输出长度含尾字符长度为17，匹配边界值，无效等价类，不考虑规格约束应输出"cc 3\nbbb 2\naaa 1"
TEST(WordFrequencyFuncTest, test_invalid_boundary_out_value_string)
{
    char* wordString = WordFrequencyFunc("aaa bbb bbb cc cc cc");
    ASSERT_TRUE(wordString != NULL);
    ASSERT_STREQ(wordString, "");
}

// 结果字符串输出长度含尾字符长度为27，匹配无效等价类，不考虑规格约束应输出"aaaaaa 3\nbbbbbb 2\ncccccc 1"
TEST(WordFrequencyFuncTest, test_invalid_string)
{
    char* wordString = WordFrequencyFunc("aaaaaa aaaaaa aaaaaa bbbbbb bbbbbb ccccccc");
    ASSERT_TRUE(wordString != NULL);
    ASSERT_STREQ(wordString, "");
}