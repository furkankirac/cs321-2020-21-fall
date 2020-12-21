#include <iostream>

//struct DivisibleBy
//{
//    int what;
//    DivisibleBy(int what) : what{what} { }
//    bool operator() (int value) const { return value % this->what == 0; }
//};

//auto divisible_by_7 = DivisibleBy(7);

auto divisible_by(int what)
{
    return [=](int value) {
        return value % what == 0;
    };
};

auto is_odd()
{
    return [](int value) {
        return value % 2 != 0;
    };
}

//template<typename ... Lambdas>
//auto all_of(int value, Lambdas ... lambdas) { return (lambdas(value) && ...); }

//template<typename ... Lambdas>
//auto any_of(int value, Lambdas ... lambdas) { return (lambdas(value) || ...); }

//template<typename ... Lambdas>
//auto none_of(int value, Lambdas ... lambdas) { return (!lambdas(value) && ...); }

//template<typename ... Lambdas>
//auto one_of(int value, Lambdas ... lambdas) { return ((int)lambdas(value) + ...) == 1; }

auto all_of_(int value, auto ... lambdas) { return (lambdas(value) && ...); }
auto any_of_(int value, auto ... lambdas) { return (lambdas(value) || ...); }
auto none_of_(int value, auto ... lambdas) { return (!lambdas(value) && ...); }
auto one_of_(int value, auto ... lambdas) { return ((int)lambdas(value) + ...) == 1; }

auto all_of(auto ... lambdas)
{
    return [=](int value) {
        return all_of_(value, lambdas...);
//        return (lambdas(value) && ...);
    };
}

template<typename Predicate, typename Action>
auto if_then(Predicate p, Action a)
{
    return [=](int x) {
        if(p(x))
            a(x);
    };
}

int main(int, char* [])
{
    auto div_by_7 = divisible_by(7);
    auto check_oddness = is_odd();
    std::cout << div_by_7(21) << std::endl;
    std::cout << check_oddness(21) << std::endl;

//    std::cout << all_of_(21, divisible_by(7), is_odd()) << std::endl;
//    std::cout << any_of_(12, divisible_by(7), is_odd()) << std::endl;
//    std::cout << none_of_(12, divisible_by(7), is_odd()) << std::endl;

    std::cout << all_of(divisible_by(7), is_odd())(21) << std::endl;

    auto IFTHEN = if_then(all_of(divisible_by(7), is_odd()), [](int value) {
        std::cout << value << " is both divisible by 7 and odd" << std::endl;
    });

    IFTHEN(21);

    return 0;
}
