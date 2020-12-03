// sizeof operator, part of reflection in C++ (check MetaClasses by Herb Sutter)
// variadic templates, parameter packs
// sizeof... operator
// compile-time stuff: types, values
// run-time stuff: values
// fold expressions

#include <iostream>
#include <string>

using namespace std;

template<int first, int ... rest> // rest is a "parameter-pack"
auto add1()
{
    if constexpr(sizeof...(rest) == 0)
        return first;
    else
        return first + add1<rest...>();
}

template<typename First, typename ... Rest> // rest is a "parameter-pack"
auto add2(First first, Rest ... rest)
{
    if constexpr(sizeof...(rest) == 0)
        return first;
    else
        return first + add2<Rest...>(rest...);
}

auto add3(auto first, auto ... rest) // divide and conquer
{
    if constexpr(sizeof...(rest) == 0)
        return first;
    else
        return first + add3(rest...);
}

auto add4(auto ... values)
{
    return (values + ...); // fold expression
}


int main(int, char* [])
{
    cout << add1<5, 10, 20>() << endl;
    cout << add1<5, 10, 20, 100>() << endl;

//    cout << add2<float, double, int, int>(5.1f, 10.2, 20, 100) << endl;
    cout << add2(5.1f, 10.2, 20, 100) << endl;
    cout << add3(5.1f, 10.2, 20, 100) << endl;
    cout << add4(5.1f, 10.2, 20, 100) << endl;
    return 0;
}
