#include <iostream>
#include "my_any.h"
int main() {
    int b = 5;
    auto a = my_any(b);

    try {
        //auto h = my_any_cast<float>(&a);
        std::cout<< my_any_cast<int>(a);
    }catch (any_cast_error & e){
        std::cout<< e.what() <<std::endl;
    }

    return 0;
}
