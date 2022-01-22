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

    Stack& operator=(const Stack& other) {
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
    [[nodiscard]] size_t size() const {
        return data.size();
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

TEST(my_any, Correct_Work_Value_Copy_Constuct) {
    int b = 5;
    auto a = my_any(b);
    EXPECT_EQ(my_any_cast<int>(a), 5);
}

TEST(my_any, Correct_Work_Move_Constuct) {
    auto a = my_any(5);
    EXPECT_EQ(my_any_cast<int>(a), 5);

    auto b = my_any(new int(4));
    EXPECT_EQ(*my_any_cast<int*>(b), 4);

    my_any c(new Stack(3));
    EXPECT_EQ(*my_any_cast<Stack*>(c), Stack(3));
}

TEST(my_any, Correct_Work_My_Any_Constuct) {
    auto a = my_any(5);
    auto b = my_any(a);
    EXPECT_EQ(my_any_cast<int>(b), 5);
}

TEST(my_any, Correct_Work_My_Any_Constuct_Nullptr) {
    auto a = my_any();
    auto b = my_any(a);
    ASSERT_THROW(my_any_cast<int>(b), any_cast_error);
}

TEST(my_any, Correct_Work_Equel_Operator_RValue) {
    my_any a(5);
    a = 4;
    EXPECT_EQ(my_any_cast<int>(a), 4);

    a = new int(4);
    EXPECT_EQ(*my_any_cast<int*>(a), 4);

    a = new Stack(3);
    EXPECT_EQ(*my_any_cast<Stack*>(a), Stack(3));
}

TEST(my_any, Correct_Work_Equel_Operator_LValue) {
    my_any a(5);
    int b = 4;
    a = b;
    EXPECT_EQ(my_any_cast<int>(a), 4);
}

TEST(my_any, Correct_Work_Equel_Operator_MyAny) {
    my_any a(5);
    my_any b(4);
    a = b;
    EXPECT_EQ(my_any_cast<int>(a), 4);

    my_any c;
    a = c;
    ASSERT_THROW(my_any_cast<float>(&a), any_cast_error);
}

TEST(my_any, Error_Type_My_Any_Cast) {
    auto a = my_any(5);
    ASSERT_THROW(my_any_cast<float>(&a), any_cast_error);
}

TEST(my_any, True_Type_My_Any_Cast_Link) {
    auto a = my_any(5);
    EXPECT_EQ(*my_any_cast<int>(&a), 5);
}

TEST(my_any, Error_Type_My_Any_Cast_Link) {
    auto a = my_any(5);
    ASSERT_THROW(my_any_cast<float>(a), any_cast_error);
}

TEST(my_any, Swap_My_Any) {
    int num1 = 5;
    float num2 = 2.2;
    auto a = my_any(num1);
    auto b = my_any(num2);
    swap(a, b);
    EXPECT_EQ(my_any_cast<float>(a), num2);
    EXPECT_EQ(my_any_cast<int>(b), num1);
}

TEST(my_any, Swap_My_Any_Nullptr) {
    int num1 = 5;
    auto a = my_any(num1);
    auto b = my_any();
    swap(a, b);
    ASSERT_THROW(my_any_cast<float>(a), any_cast_error);
    EXPECT_EQ(my_any_cast<int>(b), num1);
}

TEST(my_any, All_Methods_With_Int_Type) {
    std::string str = "Foo";
    auto a = my_any();
    a = 1;
    EXPECT_EQ(my_any_cast<int>(a), 1);

    int num = 2;
    a = num;
    EXPECT_EQ(my_any_cast<int>(a), 2);

    auto b = my_any(3);
    EXPECT_EQ(my_any_cast<int>(b), 3);

    b = a;
    EXPECT_EQ(my_any_cast<int>(b), 2);

    auto c = my_any(num);
    EXPECT_EQ(my_any_cast<int>(c), 2);

    auto d(a);
    EXPECT_EQ(my_any_cast<int>(d), 2);

    int* f = new int(4);
    my_any e(f);
    EXPECT_EQ(my_any_cast<int*>(e), f);

    swap(a, b);
    EXPECT_EQ(my_any_cast<int>(a), 2);
    EXPECT_EQ(my_any_cast<int>(b), 2);
}

TEST(my_any, Chang_Value) {
    Stack st(5);
    my_any a(st);
    Stack st_1(st);
    st.pop();
    st.push(1);
    EXPECT_EQ((my_any_cast<Stack>(a)), st_1);
}

TEST(my_any, Differences_My_Any_Casts) {
    my_any a(5);

    auto b = my_any_cast<int>(a);
    b = 3;
    EXPECT_EQ(my_any_cast<int>(a), 5);

    auto c = my_any_cast<int>(&a);
    *c = 2;
    EXPECT_EQ(my_any_cast<int>(a), 2);
}