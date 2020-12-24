// "some string" --> type of this is "const char*" not std::string

// use custom literals to represent std::string constants easily such as "some string"_s
//  or use "std::string("some string")

// std::tuple, is_tuple, is_tuple_v
// std::get<T>, std::get<index>
// tuple_element_t<index, T>
// tuple_size_v<T>

// type aliasing vs creating a new struct by inheriting
// std::pair<int, int> ---> use for representing a range of dates

// writing a generic Concept for detecting all kinds of lambdas is not possible
// you can design your own Function Object base class and write all lambdas in the form of function objects
//  that inherit your base class, and check base class availability as a parent
//  however, not fancy.
//  So, in generic programming you generally use concepts to constrain to the types that are not lambdas
//   and everything else is considered to be lambda. Hence, typename is used to represent lambdas.

#include <iostream>
#include <string>

auto operator"" _s(const char* str, size_t) { return std::string(str); }

int main(int, char* [])
{
//    const char* s1 = "Hello";
//    const char* s2 = "Hello";

    auto i = 10; // integer
    auto d = 10.5; // double
    auto f = 20.3f; // float
    auto li = 10l;
    auto s1 = "Hello"_s; //  std::string("Hello");
    auto s2 = "Hello"_s;
    std::cout << (size_t)&s1[0] << std::endl;
    std::cout << (size_t)&s2[0] << std::endl;
    std::cout << (s1 == s2) << std::endl;

    return 0;
}
