#ifndef MY_ANY_MY_ANY_H
#define MY_ANY_MY_ANY_H
#include <iostream>
#include <stdexcept>

namespace utils {
    class any_cast_error: public std::runtime_error {
    public:
        explicit any_cast_error(const std::string& msg): std::runtime_error(msg) {}
    };

    class my_any {
    public:
        my_any()= default;

        template<typename U>
        explicit my_any(const U& value) :storage_(new Derived<U>(value)){}

        template<typename U>
        explicit my_any(const U&& value) :storage_(new Derived<U>(value)){}

        // Copy value from another my_any
        my_any(const my_any& a) {
            if (a.storage_)
                storage_ = a.storage_->get_copy();
        }

        ~my_any() {
            delete storage_;
        }

        //Copy value of type U to storage
        template<typename U>
        my_any& operator=(const U& value) {
            delete storage_;
            storage_ = new Derived<U>(value);
            return *this;
        }

        // Copy storage form another my_any
        my_any& operator=(const my_any& a) {
            if (this != &a) {
                if (!a.storage_) {
                    storage_ = a.storage_;
                    return *this;
                }
                delete storage_;
                storage_ = a.storage_->get_copy();
            }
            return *this;
        }

        friend void swap(my_any& a, my_any& b);

        template<typename T>
        friend T my_any_cast(my_any& a);

        template<typename T>
        friend T * my_any_cast(const my_any* a);

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

    // Swap values of two my_any
    void swap(my_any& a, my_any& b) {
        std::swap(a.storage_, b.storage_);
    }

    // Return a copy of the value contained in my_any if the type matches
    // Else  throw any_cast_error
    // If storage == nullptr throw any_cast_error
    template<typename T>
    T my_any_cast(my_any& a) {
        auto *child = dynamic_cast<my_any::Derived<T>*>(a.storage_);

        if (!child)
            throw any_cast_error("Wrong type");
        return child->value_;
    }

    // Return a pointer to the value inside my_any if the type matches
    // Else  throw any_cast_error
    // If storage == nullptr throw any_cast_error
    template<typename T>
    T * my_any_cast(const my_any* a) {
        auto *child = dynamic_cast<my_any::Derived<T>*>(a->storage_);

        if (!child)
            throw any_cast_error("Wrong type");
        return &child->value_;
    }
}

#endif //MY_ANY_MY_ANY_H
