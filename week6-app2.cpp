// make a container from ordinary C array: make it suitable for container based generic algorithms
// std::array vs std::vector ---- compile-time vs run-time
// transform algorithm
// filter algorithm
// count_if algorithm
// lambda vs function object
// mutable lambda

#include <iostream>
#include <array>

using namespace std;

template<typename T, int sz>
struct Array
{
    T values[sz];

    template<typename U, int sz_>
    struct ConstArrayIterator
    {
        const U* beginning_ptr;
        int index;

        bool operator==(const ConstArrayIterator<U, sz_>& right) const { return index == right.index; }
        auto operator++() { return ++index; }
        auto operator++(int) { return index++; }
        U& operator*() const { return beginning_ptr[index]; }
    };

    auto begin() const { return ConstArrayIterator<T, sz>{&values[0], 0}; }
    auto end() const { return ConstArrayIterator<T, sz>{&values[0], sz}; }
    auto size() const { return sz; }
};


template<typename Container>
void print_container(const Container& container)
{
    for(const auto& item : container)
        cout << item << " ";
    cout << endl;
}


int main(int argc, char* argv[])
{
//    auto a = Array<int, 4>{10, 20, 30, 40}; // std::array
    auto a = array<int, 4>{10, 20, 30, 40}; // std::array
    auto s = a.size();
    cout <<  "size=" << s << endl;

    print_container(a);


//    for(auto item : a)
//    {
//    }

    for(auto iter=a.begin(); iter!=a.end(); ++iter)
    {
        const auto& item = *iter;
    }

    return 0;
}
