// const, volatile, reference (&), pointer (*) modifiers
// std::remove_cvref<T>::type, remove_cvref_t<T>

// accumulate algorithm, adder function
// lifted (higher order) accumulate algorithm, adder_lifed function

#include <iostream>
#include <vector>

template<typename T>
concept IsContainer = requires(T t) {
    t.begin();
    t.end();
    t.size();
};

template<typename T>
void print(const T& value)
{
    if constexpr(IsContainer<T>)
    {
        for(const auto& item : value)
            std::cout << "[" << item << "]";
        std::cout << std::endl;
    }
    else
    {
        std::cout << value << std::endl;
    }
}

struct Print { } PRINT; // taggers, tagging stuff

auto adder = []<typename T>(T a, T b) { return a+b; };
auto multiplier = [](int a, int b) { return a*b; };

auto adder_lifted()
{
    return []<typename T>(T a, T b) { return a+b; };
}

template<typename T>
auto accumulate(const IsContainer auto& container, auto func, T init_val)
{
    for(auto item : container)
        init_val = func(init_val, T(item));
    return init_val;
}

template<typename Left, typename Right>
auto operator|(const Left& left, Right right)
{
    if constexpr(std::is_same_v<Right, Print>)
    {
        print(left);
        return left;
    }
    else
    {
        return right(left);
    }
}

//auto operator|(const auto& left, Print) { print(left); return left; }

//auto operator|(const IsContainer auto& container, auto lambda) { return lambda(container); }

template<typename T>
auto accumulator(auto func, T init_val)
{
    return [=](const IsContainer auto& container) mutable {
        auto func_ = func();
        for(auto item : container)
            init_val = func_(init_val, T(item));
        return init_val;
    };
}



int main(int, char* [])
{
    auto v = std::vector<int>{1, 50, -3};
//    print(v);

//    auto sum = 0.0;
//    for(auto item : v) // raw for loops
//        sum += item;
//    auto sum = accumulate(v, adder, 0.0); // sum is double although vector's contents are int because of 0.0's type
//    print(sum);

//    auto product = 1;
//    for(auto item : v)
//        product *= item;
//    auto product = accumulate(v, multiplier, 1);
//    print(product);

    std::vector<int>{1, 50, -3} | PRINT | accumulator(adder_lifted, 0.0) | PRINT;
//    std::vector<int>{1, 50, -3} | accumulator(adder_lifted, 0.0) | PRINT;
//    48.0 | PRINT;
    return 0;
}
