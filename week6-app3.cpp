// transform algorithm
// filter algorithm
// count_if algorithm
// lambda vs function object
// mutable lambda

#include <iostream>
#include <array>

using namespace std;

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

struct GreaterThan3
{
    bool operator() (int value) const
    {
        return value > 3;
    }

//    GreaterThan3() { }
};

template<typename Container, typename FuncObj>
int count_if(const Container& container, FuncObj fobj)
{
    auto cnt = 0;
    for(const auto& item : container)
        if(fobj(item))
            ++cnt;

    return cnt;
}

template<typename Container, typename FuncObj>
void transform(Container& container, FuncObj fobj)
{
    for(auto& item : container)
        fobj(item);
}


int main(int argc, char* argv[])
{
    auto a = array<int, 5>{1, 2, 3, 4, 5};
    transform(a, [](int& a) { ++a; }); // a is now {2, 3, 4, 5, 6}

//    auto greater_than_3 = GreaterThan3();
//    auto greater_than_3 = [](int value) { return value > 3; };
    auto greater_than_1 = [](int value) { return value > 1; };

    auto cnt = count_if(a, greater_than_1);
    cout << "Count=" << cnt << endl;

    auto fg = FiboGenerator();
    for(int i=0; i<10; ++i)
        cout << fg() << " ";
    cout << endl;

    return 0;
}
