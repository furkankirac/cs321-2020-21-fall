// "transform" algorithm with function pointers
// encapsulating functions:
//   functions themselves (with func pointers),
//   function objects,
//   lambda functions

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void print(const T& a)
{
    for(const auto& item : a)
        cout << item << " ";
    cout << endl;
}

template<typename T>
struct Increment
{
    T by_what;

    void operator() (T& item)
    {
        item += by_what;
    }
};

struct Square
{
    template<typename T>
    void operator() (T& item)
    {
        item = item*item;
    }
};

//int by_what;
//void increment(int& item)
//{
//    item += by_what;
//}

//void increment_by5(int& item)
//{
//    item += 5;
//}

//void square(int& item)
//{
//    item = item*item;
//}


//typedef void(*TransformFunc)(int&);
//using TransformFunc = void(*)(int&);

//void transform(vector<int>& container, TransformFunc func)
//{
//    for(auto& item : container)
//        func(item);
//}

template<typename T, typename TransformFuncObj>
void transform(T& container, TransformFuncObj func)
{
    for(auto& item : container)
        func(item);
}

int main(int argc, char* argv[])
{
//    auto increment_by5 = Increment{5};
//    auto increment_by10 = Increment{10};
////    increment.operator()();
//    auto i = 100;
//    for(int k=0; k<3; ++k)
//        increment_by5(i);
//    cout << i << endl;

    auto v = vector<float>{10.1, 20.2, 30.3};
    print(v);

//    by_what = 3;
    transform(v, Increment<float>{3.5f});
    print(v);

//    transform(v, Square{});
    auto square = [](auto& item) { item = item*item; };
    transform(v, square);
    print(v);

    return 0;
}
