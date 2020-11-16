#include <iostream>
#include <vector>

using namespace std;

// lambda functions, stateful lambdas, generic lambdas

// constexpr, if constexpr

// pure functions != free functions
// pure functions are better. eliminate state if possible.
// if state is definitely required, better use OOP to encapsulate it from the outside world

// 1, 1, 2, 3, 5, 8, 13, ...
struct FiboGenerator
{
    int a = 0;
    int b = 1;

    int operator() ()
    {
        int c = a+b;
        a = b;
        b = c;
        return a;
    }
};

// this function object's business logic requires both number during call time
struct DivisibleBy_
{
    bool operator() (int by_what, int number) const {
        return number % by_what == 0;
    }
};

// this function object's business logic requires a number to be checked by divisible of another number called by_what
// by_what is constructed during func-obj's construction only once
struct DivisibleBy
{
    const int& by_what;
//    DivisibleBy(int by_what) : by_what(by_what) { }

    template<typename T>
    bool operator() (T number) const {
        return number % by_what == 0;
    }
};

template<typename Container, typename Lambda>
auto count_if(const Container& container, Lambda lambda)
{
    auto counter = 0;
    for(const auto& item : container)
        if(lambda(item))
            ++counter;
    return counter;
}


int main(int argc, char* argv[])
{
    {
        auto v = vector<int>{10, 20, 30, 40, 33, 44};
        auto by_what = 11;
        auto lambda = [&by_what](int item) { return item % by_what == 0; };

        auto number_of_values_divisible_by_11 = count_if(v, lambda);
        cout << number_of_values_divisible_by_11 << endl;

        by_what = 10;
        auto number_of_values_divisible_by_10 = count_if(v, lambda);
        cout << number_of_values_divisible_by_10 << endl;
    }

    {
        auto divisible_by_7 = DivisibleBy{7};
        cout << (divisible_by_7(14) ? "true" : "false") << endl;
        cout << (divisible_by_7(13) ? "true" : "false") << endl;
        cout << (DivisibleBy{7}(14) ? "true" : "false") << endl;
        cout << (DivisibleBy_()(7, 14) ? "true" : "false") << endl;

        auto by_what = 13;
        auto divisible_by_lambda = [&by_what](auto number) { return number % by_what == 0; };
        cout << (divisible_by_lambda(14) ? "true" : "false") << endl;

        by_what = 7;
        cout << (divisible_by_lambda(13) ? "true" : "false") << endl;
    }

    {
        auto fibo = FiboGenerator();
        for(int i=0; i<10; ++i)
            cout << fibo() << " ";
        cout << endl;
    }

    {
        auto fibo_lambda = [a=0, b=1]() mutable {
            int c = a+b;
            a = b;
            b = c;
            return a;
        };
        for(int i=0; i<10; ++i)
            cout << fibo_lambda() << " ";
        cout << endl;
    }

    return 0;
}
