#include <gtest/gtest.h>
#include <string>
#include "my_any.h"

using namespace utils;

// CR: test that invokes all of my_any methods
// CR: tests with custom class (especially where copy ctor should be invoked)

TEST(my_any, CorrectWorkValueCopyConstuct) {
    int b = 5;
    auto a = my_any(b);
    EXPECT_EQ(my_any_cast<int>(a), 5);
}

TEST(my_any, CorrectWorkMoveConstuct) {
    auto a = my_any(5);
    EXPECT_EQ(my_any_cast<int>(a), 5);
}

TEST(my_any, CorrectWorkMyAnyConstuct) {
    auto a = my_any(5);
    auto b = my_any(a);
    EXPECT_EQ(my_any_cast<int>(b), 5);
}

TEST(my_any, CorrectWorkMyAnyConstuctNullptr) {
    auto a = my_any();
    auto b = my_any(a);
    ASSERT_THROW(my_any_cast<int>(b), any_cast_error);
}

TEST(my_any, CorrectWorkEquelOperatorLValue) {
    my_any a(5);
    a = 4;
    EXPECT_EQ(my_any_cast<int>(a), 4);
}

TEST(my_any, CorrectWorkEquelOperatorRValue) {
    my_any a(5);
    int b = 4;
    a = b;
    EXPECT_EQ(my_any_cast<int>(a), 4);
}

TEST(my_any, CorrectWorkEquelOperatorMyAny) {
    my_any a(5);
    my_any b(4);
    a = b;
    EXPECT_EQ(my_any_cast<int>(a), 4);
}

TEST(my_any, ErrorTypeMyAnyCast) {
    auto a = my_any(5);
    ASSERT_THROW(my_any_cast<float>(&a), any_cast_error);
}

TEST(my_any, TrueTypeMyAnyCastLink) {
    auto a = my_any(5);
    EXPECT_EQ(*my_any_cast<int>(&a), 5);
}

TEST(my_any, ErrorTypeMyAnyCastLink) {
    auto a = my_any(5);
    ASSERT_THROW(my_any_cast<float>(a), any_cast_error);
}

TEST(my_any, SwapMyAny) {
    int num1 = 5;
    float num2 = 2.2;
    auto a = my_any(num1);
    auto b = my_any(num2);
    swap(a, b);
    EXPECT_EQ(my_any_cast<float>(a), num2);
    EXPECT_EQ(my_any_cast<int>(b), num1);
}

TEST(my_any, SwapMyAnyNullptr) {
    int num1 = 5;
    auto a = my_any(num1);
    auto b = my_any();
    swap(a, b);
    ASSERT_THROW(my_any_cast<float>(a), any_cast_error);
    EXPECT_EQ(my_any_cast<int>(b), num1);
}
