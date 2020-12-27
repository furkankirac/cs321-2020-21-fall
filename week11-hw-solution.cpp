#include <iostream>
#include <vector>
#include <array>
#include <list>

template<typename T>
concept IsContainer = requires(T t)
{
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

auto printer()
{
    return [](const auto& value) { print(value); return value; };
}

// swap functionality
template<typename T> void swap(T& a, T& b) { auto temp = a; a = b; b = temp; }

auto reverse()
{
    return [](const IsContainer auto& container) {
        auto c = container;
        auto sz = container.size(); // return size_t type which is for this architecture unsigned long
        auto k = sz/2;
        auto it_begin = c.begin();
        auto it_end = c.end();
        for(auto i=size_t(0); i<k; ++i)
            swap(*it_begin++, *--it_end);
        return c;
    };
}

// everything is available here, we just calculate what we want right away
bool higher_than_(int a, int what) { return a > what; }

// only what part is available, we create a function object that waits for the a value
auto higher_than(auto what) { return [=](auto a) { return higher_than_(a, what); }; }


template<IsContainer Container>
auto filter_(const Container& container, auto lambda)
{
    auto c = Container(container.size());
    auto it = c.begin();
    for(const auto& item : container)
        if(lambda(item))
            *it++ = item;
    return c;
}

template<typename T, size_t sz>
auto filter_(const std::array<T, sz>& container, auto lambda)
{
    auto c = std::array<T, sz>();
    auto it = c.begin();
    for(const auto& item : container)
        if(lambda(item))
            *it++ = item;
    return c;
}

auto filter(auto lambda)
{
    return [=](const auto& container) { // Container is here std::vector<int>
        return filter_(container, lambda);
    };
}

template<size_t count, typename T, size_t sz>
auto take_(const std::array<T, sz>& container)
{
    // let's say:
    // container is of the type "std::array<int, 6>"
    // want to create a new container instance such as
    // std::array<int, 3>
    // count is 3 (count needs to be a compile-time template parameter,
    //  so that we can use it in std::array<int, count>)

    auto c = std::array<T, count>{}; // count is compile-time param.
    auto i = size_t(0);
    for(auto it = container.begin(); i<count; ++i, ++it)
        c[i] = *it;
    return c;
}

template<size_t count, IsContainer Container>
auto take_(const Container& container)
{
    auto c = Container();
    auto i = size_t(0);
    for(auto it = container.begin(); i<count; ++i, ++it)
        c.push_back(*it);
    return c;
}

template<size_t count>
auto take()
{
    return [=]<IsContainer Container>(const Container& container) {
        return take_<count>(container);
    };
}

auto add(auto value)
{
    return [=](auto item) {
        return item + value;
    };
}

template<IsContainer Container>
auto transform_(const Container& container, auto func)
{
    auto c = container;
    for(auto& item : c)
        item = func(item);
    return c;
}

auto transform(auto func)
{
    return [=](const auto& container) {
        return transform_(container, func);
    };
}

auto adder()
{
    return []<typename T>(T a, T b) { return a+b; };
}

template<typename T>
auto accumulator(auto func_lifted, T init_val)
{
    return [=](const IsContainer auto& container) mutable {
        auto func = func_lifted();
        for(auto item : container)
            init_val = func(init_val, T(item));
        return init_val;
    };
}

auto operator|(const auto& anything, auto lambda) { return lambda(anything); }

int main(int, char* [])
{
    auto PRINT = printer();

    std::array<int, 6>{1, 50, -3, 5, -10, 100}
        | PRINT
        | reverse() | PRINT
        | filter(higher_than(0)) | PRINT
        | take<3>() | PRINT
        | transform(add(10)) | PRINT
        | accumulator(adder, 0) | PRINT;

    std::vector<int>{1, 50, -3, 5, -10, 100}
        | PRINT
        | reverse() | PRINT
        | filter(higher_than(0)) | PRINT
        | take<3>() | PRINT
        | transform(add(10)) | PRINT
        | accumulator(adder, 0) | PRINT;

    return 0;
}
