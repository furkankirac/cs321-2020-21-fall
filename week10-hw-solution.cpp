#include <iostream>
#include <map>
#include <string>

template<typename T>
struct Value
{
    T value;
    auto operator<(const Value<T>& other) const {
        return value < other.value;
    }
};

template<typename T>
concept has_value = requires(T t) {
    t.value;
};

template<typename T1, typename T2>
requires((has_value<T1> && !has_value<T2>) || (!has_value<T1> && has_value<T2>))
void print(const std::map<T1, T2>& m)
{
    for(const auto& [t1, t2] : m)
    {
        if constexpr(has_value<T2>)
            std::cout << "Key: " << t1 << ", Value: " << t2.value << std::endl;
        else
            std::cout << "Key: " << t2 << ", Value: " << t1.value << std::endl;
    }
}

int main(int, char* [])
{
    auto m1 = std::map<int, Value<std::string>>{
        {10, {"Ten"}},
        {12, {"Twelve"}},
        {20, {"Twenty"}},
    };
    print(m1);

    auto m2 = std::map<Value<double>, char>{
        {{3.14}, 'p'},
        {{2.72}, 'e'},
    };
    print(m2);
    return 0;
}
