// some fancy type traits
//  is_integral<int>::value
//  is_same<int, int>::value
//  conditional<boolean_value, T1, T2>::type

// some fancy concepts (compile-time validation of types):
//  integral, same_as, ...

template<typename T>
struct TypeDisplayer;

#include <iostream>
#include <string>

// using namespace std;

template<typename T> struct is_integral        { static const bool value = false; };
template<>           struct is_integral<int>   { static const bool value = true; };
template<>           struct is_integral<short> { static const bool value = true; };
template<>           struct is_integral<char>  { static const bool value = true; };
template<>           struct is_integral<long>  { static const bool value = true; };

// we don't use this method (function templates), because overloading functions are very easy
// 3rd parties can overload our functions to change their behavior
//template<typename T> constexpr bool IS_INTEGRAL(T) { return false; }
//template<>           constexpr bool IS_INTEGRAL(int) { return true; }
//template<>           constexpr bool IS_INTEGRAL(short) { return true; }
//template<>           constexpr bool IS_INTEGRAL(char) { return true; }
//template<>           constexpr bool IS_INTEGRAL(long) { return true; }

template<typename T1, typename T2> struct is_same       { static const bool value = false; };
template<typename T>               struct is_same<T, T> { static const bool value = true; };

template<bool B, typename T1, typename T2> struct conditional                { using type = T1; };
template<typename T1, typename T2>         struct conditional<false, T1, T2> { using type = T2; };

// we have seen function templates, class/struct templates
// now: variable templates
template<typename T>
constexpr bool is_integral_v = is_integral<T>::value;

template<typename T1, typename T2>
constexpr bool is_same_v = is_same<T1, T2>::value;

// now: type templates
template<bool B, typename T1, typename T2>
using conditional_t = typename conditional<B, T1, T2>::type;

// concept versions of is_integral and is_same
// we need concept versions so that we use them as constraints in generic programming
// instead of typename which matches every type, we can now restrict types to match integral<T>, same_as<T1, T2>
template<typename T>
concept integral = is_integral_v<T>;

template<typename T1, typename T2>
concept same_as = is_same_v<T1, T2>;

// most generic print function
//template<typename T> void print(T t) { std::cout << t << std::endl; }

// print function that requires an integral type
//template<integral T> void print(T t) { std::cout << t << std::endl; }

// print function that requires an integral type (again with another way of writing it)
//template<typename T>
//requires integral<T>
//void print(T t)
//{ std::cout << t << std::endl; }

// print function that requires an integral type (again with another way of writing it)
//template<typename T>
//void print(T t)
//requires integral<T>
//{ std::cout << t << std::endl; }

// print function that requires an integral type (again with another way of writing it called terse syntax)
//void print(integral auto t) { std::cout << t << std::endl; }

// print(5, 10, string("Hello"), 3.14); is deduced as below:
// print<int, int, std::string, double>(5, 10, string("Hello"), 3.14);

// what is Ts containing? (compile time types) Ts contains (int, int, std::string, double)
// what is ts containing? (run-time values)    ts contains (5, 10, string("Hello"), 3.14

// a print function that accepts any number of type-values obeying the integral concept
template<integral ... Ts>
void print(Ts ... ts)
{
    // use fold expressions with "operator,"
    // evaluate each parameter pack element
    ((std::cout << ts << std::endl), ...);
}

auto foo() { return 10; }

auto bar(int a) { return a+1; }

auto func()
{
    // foo() is evaluated, 10 is returned
    // bar(5) is evaluated 6 is returned
    // we do nothing with returned 10 and 6
    // but return 40
    return foo(), bar(5), 40;
}

int main(int, char* [])
{
    auto i = func(); // i is int, its value is 40

//    std::cout << is_integral<float>::value << std::endl; // false
//    std::cout << is_integral<int>::value << std::endl; // true
    std::cout << is_integral_v<float> << std::endl; // false
    std::cout << is_integral_v<int> << std::endl; // true

//    std::cout << "func: " << IS_INTEGRAL(float()) << std::endl; // false
//    std::cout << "func: " << IS_INTEGRAL(int()) << std::endl; // true

//    std::cout << is_same<int, float>::value << std::endl; // false
//    std::cout << is_same<double, double>::value << std::endl; // true
    std::cout << is_same_v<int, float> << std::endl; // false
    std::cout << is_same_v<double, double> << std::endl; // true

//    TypeDisplayer< conditional<false, int, float>::type > a;
//    TypeDisplayer< conditional_t<false, int, float> > a;

    std::cout << "----" << std::endl;
    print(5, 10); //, std::string("Hello"), 3.14);
//    print(short(5));
//    print(long(5));
//    print('5');
//    print(5.5);
//    print(5.5f);
//    print("Hi there");

    return 0;
}
