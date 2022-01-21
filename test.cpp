#include <gtest/gtest.h>
#include <string>
#include "my_any.h"

using namespace utils;

class Stack {
private:
    std::vector<int> data;
public:
    explicit Stack(const int a){
        data.push_back(a);
    }

    ~Stack() = default;

    Stack(const Stack& other) { data = other.data; }

    Stack& operator= (const Stack& other) {
        if (this != &other)
            data = other.data;
        return *this;
    }

    void push(int a){
        data.push_back(a);
    }
    int pop(){
        int a = data.back();
        data.pop_back();
        return a;
    }
    int back(){
        return data.back();
    }
    [[nodiscard]] size_t size() const {
        return data.size();
    }
    bool empty(){
        return data.empty();
    }
    friend bool operator==(const Stack& a, const Stack& b);
};
bool operator==(const Stack& a, const Stack& b) {
    if (a.size() != b.size())
        return false;
    auto j = b.data.begin();
    for (auto i = a.data.begin(); i < a.data.end(); ++i) {
        if (*i != *j)
            return false;
    }
    return true;
}

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

TEST(my_any, AllMethods) {
    std::string str = "Foo";
    auto a = my_any();
    a = 9;
    auto b = my_any(a);
    EXPECT_EQ(my_any_cast<int>(b), 9);
    a = str;
    swap(a, b);
    EXPECT_EQ(my_any_cast<int>(a), 9);
    // CR: invoke all methods with int type
    EXPECT_EQ(my_any_cast<int>(b), 9);
}

TEST(my_any, CustomClass) {
    Stack st(5);
    my_any a(st);
    EXPECT_EQ(my_any_cast<Stack>(a), st);
}

/*
 * CR:
 * 0. create A a
 * 1. create new any(a)
 * 2. change something inside of a
 * 3. will any(a) also change?
 */

// CR: test my_any_cast(const my_any* a), my_any_cast(const my_any a) : check if they behave differently