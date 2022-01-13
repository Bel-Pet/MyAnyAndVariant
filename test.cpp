#include <gtest/gtest.h>
#include <string>
#include "my_any.h"

using namespace utils;

// CR: invoke all of the my_any methods for some type


TEST(my_any, CorrectWorkEqualOperator) {
    int b = 5;
    my_any a(b);
    a = 4;

    auto h = my_any_cast<int>(&a);
    EXPECT_EQ(h, 4);
}

TEST(my_any, CorrectWorkMyAnyMoveConstuct) {
    auto a = my_any(5);

    auto h = my_any_cast<int>(&a);
    EXPECT_EQ(h, 5);
}

TEST(my_any, TrueWorkMyAnyCastAndValueCopyConstuct) {
    int b = 5;
    auto a = my_any(b);

    auto h = my_any_cast<int>(&a);
    EXPECT_EQ(h, 5);
}

TEST(my_any, ErrorTypeWorkMyAnyCast) {
    int b = 5;
    auto a = my_any(b);

    EXPECT_THROW(my_any_cast<float>(&a), any_cast_error);
}

TEST(my_any, TrueMyAnyCastLink) {
    int b = 5;
    auto a = my_any(b);
    auto h = my_any_cast<int>(a);
    // CR: new test to check that this is not a copy
    EXPECT_EQ(*h, 5);
}



TEST(my_any, ErrorTypeMyAnyCastLink) {
    int b = 5;
    auto a = my_any(b);

    // CR: expect throw
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

    swap(a, b);
    auto h = my_any_cast<int>(&a);
    auto g = my_any_cast<int>(&b);
    EXPECT_EQ(h, 2);
    EXPECT_EQ(g, 5);
}