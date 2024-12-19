#include "gtest/gtest.h"
#include "iostream"

TEST(MainTest, Multiply) { ASSERT_EQ(true, true) << "Hello world!"; }

TEST(MainTest, test) { std::cout << "CPP Version: " << __cplusplus << "\n"; }