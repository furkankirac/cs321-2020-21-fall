#include <iostream>
#include <array>
#include <vector>

using namespace std;

struct IntGreaterThanX
{
    int x;
    bool operator() (int value) const { return value > x; }
};

template<typename T>
struct GreaterThanX
{
    T x;
    bool operator() (T value) const { return value > x; }
};

struct Everything
{
    template<typename T>
    bool operator() (const T&) const { return true; }
};

template<typename T>
auto greater_than_x(const T& x)
{
    return GreaterThanX<T>{x};
}

template<typename Container, typename FuncObj>
auto print(const Container& container, FuncObj fobj)
{
    for(const auto& item : container)
        if(fobj(item))
            cout << item << " ";
    cout << endl;
}

int main(int argc, char* argv[])
{
    auto gt_10 = IntGreaterThanX{10};
    cout << gt_10(5) << endl;
    cout << gt_10(11) << endl;

    auto gt_pi = GreaterThanX<float>{3.14f};
    cout << gt_pi(3.0f) << endl;
    cout << gt_pi(11.0f) << endl;

    auto gt_pi2 = greater_than_x(3.14f);
    cout << gt_pi2(3.0f) << endl;
    cout << gt_pi2(11.0f) << endl;

    auto a = std::array<float, 2>{2.2f, 6.6f};
    print(a, Everything());
    print(a, gt_pi);
    auto v = std::vector<int>{5, 10, 20};
    print(v, Everything());
    print(v, gt_10);

    return 0;
}
