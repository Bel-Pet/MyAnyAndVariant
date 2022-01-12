#include <gtest/gtest.h>
#include <string>
#include "my_any.h"

using namespace utils;

TEST(my_any, CorrectWorkEquelOperator) {
    int b = 5;
    my_any a(b);
    a = 4;

    try {
        auto h = my_any_cast<int>(&a);
        EXPECT_EQ(h, 4);
    }catch (any_cast_error & e){
        std::string expected = "Wrong type";
        bool result = e.what() == expected;
        EXPECT_TRUE(!result);
    }
}

TEST(my_any, CorrectWorkMyAnyMoveConstuct) {
    int b = 5;
    auto a = my_any(5);

    try {
        auto h = my_any_cast<int>(&a);
        EXPECT_EQ(h, b);
    }catch (any_cast_error & e){
        std::string expected = "Wrong type";
        bool result = e.what() == expected;
        EXPECT_TRUE(!result);
    }
}

TEST(my_any, TrueWorkMyAnyCastAndValueCopyConstuct) {
    int b = 5;
    auto a = my_any(b);

    try {
        auto h = my_any_cast<int>(&a);
        EXPECT_EQ(h, b);
    }catch (any_cast_error & e){
        std::string expected = "Wrong type";
        bool result = e.what() == expected;
        EXPECT_TRUE(!result);
    }
}

TEST(my_any, ErrorTypeWorkMyAnyCast) {
    int b = 5;
    auto a = my_any(b);

    try {
        auto h = my_any_cast<float>(&a);
        EXPECT_EQ(h, 2);
    }catch (any_cast_error & e){
        std::string expected = "Wrong type";
        bool result = e.what() == expected;
        EXPECT_TRUE(result);
    }
}

TEST(my_any, TrueMyAnyCastLink) {
    int b = 5;
    auto a = my_any(b);

    try {
        auto h = my_any_cast<int>(a);
        EXPECT_EQ(*h, b);
    }catch (any_cast_error & e){
        std::string expected = "Wrong type";
        bool result = e.what() == expected;
        EXPECT_TRUE(!result);
    }
}

TEST(my_any, ErrorTypeMyAnyCastLink) {
    int b = 5;
    auto a = my_any(b);

    try {
        auto h = my_any_cast<float>(a);
        EXPECT_EQ(*h, 2);
    }catch (any_cast_error & e){
        std::string expected = "Wrong type";
        bool result = e.what() == expected;
        EXPECT_TRUE(result);
    }
}

TEST(my_any, SwapMyAny) {
    int num1 = 5;
    int num2 = 2;
    auto a = my_any(num1);
    auto b = my_any(num2);

    try {
        swap(a, b);
        auto h = my_any_cast<int>(&a);
        auto g = my_any_cast<int>(&b);
        EXPECT_EQ(h, num2);
        EXPECT_EQ(g, num1);
    }catch (any_cast_error & e){
        std::string expected = "Wrong type";
        bool result = e.what() == expected;
        EXPECT_TRUE(!result);
    }
}