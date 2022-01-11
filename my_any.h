#ifndef MY_ANY_MY_ANY_H
#define MY_ANY_MY_ANY_H
#include <iostream>

class my_any {
public:
    template<typename U>
    explicit my_any(const U& value) :storage_(new Derived<U>(value)){}

    ~my_any() {
        delete storage_;
    }

    my_any(const my_any& a) : storage_(a.storage_->get_copy()) {}

    template<typename U>
    my_any& operator=(const U& value) {
        delete storage_;
        storage_ = new Derived<U>(value);
    }

private:
    struct Base {
        virtual Base* get_copy() = 0;
        virtual ~Base()= default;
    };

    template<typename T>
    struct Derived : public Base {
        T value_;
        explicit Derived(const T& value) : value_(value) {}

        Base* get_copy() override {
            return new Derived<T>(value_);
        }
    };

    Base* storage_ = nullptr;
};

#endif //MY_ANY_MY_ANY_H
