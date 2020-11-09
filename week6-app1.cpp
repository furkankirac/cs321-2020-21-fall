// make a container from ordinary C array: make it suitable for container based generic algorithms
// std::array vs std::vector ---- compile-time vs run-time
// transform algorithm
// filter algorithm
// count_if algorithm
// lambda vs function object
// mutable lambda

#include <iostream>

using namespace std;

template<typename T, int sz>
struct ConstArrayIterator
{
    const T* beginning_ptr;
    int index;
};


template<typename U, int sz_>
bool operator==(const ConstArrayIterator<U, sz_>& left, const ConstArrayIterator<U, sz_>& right)
{
    return left.index == right.index;
}

template<typename U, int sz_>
auto operator++(ConstArrayIterator<U, sz_>& iter)
{
    return ++iter.index;
}

template<typename U, int sz_>
auto operator++(ConstArrayIterator<U, sz_>& iter, int unused)
{
    return iter.index++;
}


template<typename U, int sz_>
U operator*(const ConstArrayIterator<U, sz_>& iter)
{
    return iter.beginning_ptr[iter.index];
}

template<typename T, int sz>
struct Array
{
    T values[sz];

    auto begin() const
    {
        return ConstArrayIterator<T, sz>{&values[0], 0}; // initialized to point to the beginning of my array
    }
    auto end() const
    {
        return ConstArrayIterator<T, sz>{&values[0], sz}; // initialized to point to the very end of my array
    }
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
    auto a = Array<int, 4>{10, 20, 30, 40}; // std::array
    auto s = a.size();
    cout <<  "size=" << s << endl;

    print_container(a);


//    for(auto item : a)
//    {
//    }

//    for(auto iter=a.begin(); iter!=a.end(); ++iter)
//    {
//        const auto& item = *iter;
//    }

    return 0;
}
