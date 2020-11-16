#include <iostream>

using namespace std;

// compile-time pure functions are represented by template meta programming in C++
// and also "constexpr" keyword. But let's skip constexpr for now.

// struct Divide<u, v>; // explicit specialization for v=0
// struct Sum<first, second>;

// variadic templates
// struct Sum<first, second, ...>; ???
// recursive version

template<int u, int v> struct Divide        { static const auto value = u / v; };
template<int k>        struct Divide<k, 0>  { static const auto value = -1; };

template<int u, int v> struct Sum2 { static const auto value = u + v; };
template<int u, int v, int y> struct Sum3 { static const auto value = u + v + y; };

template<int u, int ... rest> struct Sum    { static const auto value = u + Sum<rest...>::value; };
template<int u>               struct Sum<u> { static const auto value = u; };

//struct Sum_10_
//{
//    static const auto value = 10 + Sum<20, 30>::value;
//};

//struct Sum_10_20_
//{
//    static const auto value = 10 + 20 + Sum<30>::value;
//};

//struct Sum_10_20_30_
//{
//    static const auto value = 10 + 20 + 30 + Sum<>::value;
//};

//struct Divide_10_2
//{
//    int value = 10 / 2;
//};

int main(int argc, char* argv[])
{
    // imperative programming
//    auto u=10;
//    auto v=0;
//    if(v==0)
//        cout << 0 << endl;
//    else
//        cout << u / v << endl;

    // pure functional programming style
//    template<int u, int v> struct Divide        { static const auto value = u / v; };
//    template<int k>        struct Divide<k, 0>  { static const auto value = -1; };
    auto d = Divide<10, 0>::value;
    cout << d << endl;

    cout << Sum2<10, 20>::value << endl;
    cout << Sum2<(Sum2<10, 20>::value), 30>::value << endl;
    cout << Sum3<10, 20, 30>::value << endl;

    cout << Sum<10, 20, 30, 40, 50, 60>::value << endl;

    return 0;
}

