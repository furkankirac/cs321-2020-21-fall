#include <iostream>
#include <map>
#include <string>

// Given below code
// You are required to make below code work
// and when it runs it needs to print output to the console as below
// Key: 10, Value: Ten
// Key: 12, Value: Twelve
// Key: 20, Value: Twenty
// Key: e, Value: 2.72
// Key: p, Value: 3.14

// std::map<Key, Value> uses its Key type as the accessor to Values
// std::map keeps things ordered by sorting its Keys in the memory
// so typename represented by Key is required to be comparable with same Key types via "operator<"

// improve Value<T> struct:
// since Value<T> is used as Key of std::map in "auto m2 = ..." part, Value<T> needs support for
// being compared with operator< (required by std::map)

// design necessary concept to check if a type is of Value<T> type
// design a print function that takes std::map<T1, T2> such that only one of T1 or T2 is a Value<U> type
// print function shall automatically understand which of T1 and T2 is of Value<U> type and print accordingly

template<typename T>
struct Value
{
    T value;
};

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
