# MyAnyAndVariant

Задание 3. any / variant

Написать один из классов: any или variant . any - позволяет хранить внутри любой тип, variant - только один из указанных типов

Общие требования для двух заданий

код должен быть покрыт тестами
классы и вспомогательные функции должны находиться в отдельном namespace (например, utils)
проект должен использовать cmake для сборки
память должна корректно очищаться
в систему сборки должен быть встроен санитайзер

any (10 баллов)

Написать класс any со следующими методами:
any(T &) - создать any на основе переданного типа
operator=(T &) - присвоить в any другой тип
operator=(any & other) присвоить в any значение из другого any
any(T &&) -  создать any на основе переданного типа (использовать move)

Также сделать следующие внешние вспомогательные функции:
T any_cast(any *)  - каст к типу Т и возврат значения из any. должно работать так же, как any_cast в boost . в случае исключения кидать свое исключение any_cast_error
swap(any &, any &) - поменять значения в двух any

variant (20 баллов)

Написать шаблонный класс variant:
variant(V &) - создать variant на основе переданного типа. тип должен быть валидирован в compile time
variant(V &&) - создать variant на основе переданного типа (использовать move). тип должен быть верифицирован в compile time
operator=(V &) - присвоить в variant другой тип. тип должен быть валидирован в compile time
operator=(variant<...> &) присвоить в variant значение из другого variant. тип должен быть валидирован в compile time

Также сделать следующие внешние вспомогательные функции:
T & get(variant<...>) - достать ссылку на объект типа T из variant. если не удалось - кинуть свое исключение variant_access_error
T * get_if(variant<...>) - достать указатель типа T из variant. если не удалось - вернуть nullptr
variant:visit (+5 баллов)

Написать функцию visit(Visitor &&, variant &&) . Функция должна работать за константное время, по принципу std::visit .

Полезные ссылки

https://www.boost.org/doc/libs/1_61_0/doc/html/boost/any.html
https://en.cppreference.com/w/cpp/utility/variant
https://stackoverflow.com/questions/4988939/how-do-boostvariant-and-boostany-work
https://en.cppreference.com/w/cpp/language/static_assert
https://diego.assencio.com/?index=834995d09abc1386a8dc5ed84d019e17
https://en.cppreference.com/w/cpp/language/dynamic_cast
https://www.youtube.com/watch?v=MF3JpSg-olg
https://www.youtube.com/watch?v=3KyW5Ve3LtI
https://isocpp.org/wiki/faq/cpp11-language-templates
https://en.cppreference.com/w/cpp/language/constexpr
https://pabloariasal.github.io/2018/06/26/std-variant/
https://en.cppreference.com/w/cpp/utility/variant/visit
