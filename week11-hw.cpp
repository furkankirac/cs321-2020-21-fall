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
        for(auto i=size_t(0); i<k; ++i)
        {
            swap(c[i], c[sz-1-i]);
//            auto temp = c[i];
//            c[i] = c[sz-1-i];
//            c[sz-1-i] = temp;
        }
        return c;
    };
}

// everything is available here, we just calculate what we want right away
bool higher_than_(int a, int what) { return a > what; }

// only what part is available, we create a function object that waits for the a value
auto higher_than(auto what) { return [=](auto a) { return higher_than_(a, what); }; }

auto filter(auto lambda)
{
    return [=]<IsContainer Container>(const Container& container) { // Container is here std::vector<int>
        auto c = Container();
        for(const auto& item : container)
            if(lambda(item))
                c.push_back(item);
        return c;
    };
}

template<IsContainer Container>
auto take_(const Container& container, size_t count)
{
    auto c = Container();
    auto i = size_t(0);
    for(auto it = container.begin(); i<count; ++i, ++it)
        c.push_back(*it);
//    for(size_t i=0; i<count; ++i)
//        c.push_back(container[i]);
    return c;
}

auto take(size_t count)
{
    return [=]<IsContainer Container>(const Container& container) {
        return take_(container, count);
    };
}

auto add(auto value)
{
    return [=](auto item) {
        return item + value;
    };
}

auto transform(auto func)
{
    return [=]<IsContainer Container>(Container& container) {
        auto c = Container();
        for(const auto& item : container)
            c.push_back(func(item));
        return c;
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
    std::vector<int>{1, 50, -3, 5, -10, 100} | printer()
        | reverse() | printer()
        | filter(higher_than(0)) | printer()
        | take(3) | printer()
        | transform(add(10)) | printer()
        | accumulator(adder, 0) | printer();

    return 0;
}
