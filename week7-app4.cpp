#include <iostream>
#include <string>
#include <vector>

// type_display trick
// std::remove_reference -> let's code ourselves

// reflection - decltype - unevaluated context
// decltype for function return type

// references are by design assigned during construction.
// non-erasable types cannot be stored in a std::vector (for instance T&)

// concepts

using namespace std;

template<typename T>
struct type_display; // forward declaration

template<typename T> struct remove_modifiers     { using type = T; };
template<typename T> struct remove_modifiers<T*> { using type = T; };
template<typename T> struct remove_modifiers<T&> { using type = T; };
template<typename T> struct remove_modifiers<const T*> { using type = T; };
template<typename T> struct remove_modifiers<const T&> { using type = T; };

template<typename T> void func1(const T& t) { }

auto func2 = [](const auto& t)
{
    // if you are using ::type after a templated type please use "typename" keyword at the very left
    using T = typename remove_modifiers< decltype(t) >::type;
//    decltype(t) t2;
    auto t2 = T();
//    auto td = type_display< T >();

    return t2;
};

int main(int argc, char* argv[])
{
//    type_display< remove_modifiers<const int&>::type >();

    func2(5);
    func2(string("hello"));

    using K = decltype( func2(5) ); // unevaluated context
//    auto td = type_display< K >();

    auto v = std::vector<int>{};

    return 0;
}
