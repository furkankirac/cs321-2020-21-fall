#include <iostream>
#include <vector>
#include <range/v3/all.hpp>

template<typename ... Ts>
using vector = std::vector<Ts...>;

using namespace ranges; // instead of ranges::*, directly use *
namespace views = ranges::views; // instead of ranges::views::*, directly use views::*

int main(int, char* [])
{
    auto horizontal_line = [] { std::cout << "------" << std::endl; };
    auto new_line = [] { std::cout << std::endl; };

    auto v1 = vector<double>{3.14, 2.7, 10.5, 20.1};
    auto v2 = vector<char>{'1', '1', '0', '1', '1'};

    { // example #1: accumulate
        // below is a single for loop implementation summing things up
        auto sum1 = accumulate(v1 | views::reverse | views::take(2), 0.0);
        std::cout << sum1 << std::endl;

        horizontal_line();

        // this is the old-school way of writing it
        auto sum2 = 0.0;
        for(size_t i=v1.size()-1; i>=v1.size()-1-2; --i)
            sum2 += v1[i];
        std::cout << sum1 << std::endl;
    }
    new_line();

    { // example #2: nested-for-loop implementation with ranges
        // below is a nested-for-loop equivalent of going over v1 and v2.
        // nesting is actually equivalent to taking cartesian_product in mathematics
        for(auto [a, b] : views::cartesian_product(v1 | views::reverse, v2))
            std::cout << "[" << a << ", " << b << "]" << std::endl;

        horizontal_line();

        // this is the old-school nested for loop version! very prone to bugs.
        for(int i=v1.size()-1; i>=0; --i)
        {
            auto a = v1[i];
            for(size_t j=0; j<v2.size()-1; ++j)
            {
                auto b = v2[j];
                std::cout << "[" << a << ", " << b << "]" << std::endl;
            }
        }
    }
    new_line();

    { // example #3: inner-product (dot-product) -> single for-loop coupled with some other action

        // this is a generator that returns 1, k^1, k^2, k^3, k^4, ... respectively for each call
        auto powers_of_k = [](auto k) {
            return [i=1, k]() mutable { return (i*=k)/k; };
        };

        // make it a ranges-library compatible generator that generate 1, 2, 4, 8, 16, ...
        auto multiples_of_2 = views::generate(powers_of_k(2));

        auto v = vector<short>{1, 1, 0, 1, 1}; // base 10 repr. of binary number: 1*1 + 2*1 + 4*0 + 8*1 + 16*1

        auto result = inner_product(v | views::reverse, multiples_of_2, 0);
        std::cout << result << std::endl;

        horizontal_line();

        // this is the old-school version! very prone to bugs.
        auto sum = 0;
        auto k = 1;
        for(int i=v.size()-1; i>=0; --i)
        {
            sum += k * v[i];
            k *= 2;
        }
        std::cout << sum << std::endl;
    }
    new_line();

    // you can easily sort things with ranges library
    {
        v1 |= actions::sort;
        for(auto a : v1)
            std::cout << a << std::endl;
    }
    new_line();

    // you can easily get non-repeating (unique) elements with ranges library
    {
        auto v = vector<int>{10, 10, 5, 5, 5, 20, 5, 10};
        v |= actions::unique; // produces 10, 5, 20, 5, 10
        for(auto a : v)
            std::cout << a << std::endl;
    }
    return 0;
}
