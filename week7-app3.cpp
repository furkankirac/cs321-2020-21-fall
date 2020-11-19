// function overloading: (overload set)
//   in reality this is partial function declaration in functional programming.
// create print_container for all types.
//   make a specialization of print_container for a specific container type via overloading

// enum / enum class

// std::vector has push_back(item) method

// std::pair
// std::map
// structured binding

// type_display trick
// std::remove_reference -> let's code ourselves

// reflection - decltype - unevaluated context
// decltype for function return type

// references are by design assigned during construction.
// non-erasable types cannot be stored in a std::vector (for instance T&)

// concepts


#include <iostream>
#include <vector>
#include <array>
#include <map>

using namespace std;

enum Gender
{
    Female, // = 0,
    Male // = 1
};


template<typename Key, typename Value>
struct Pair // similar to std::pair
{
    Key first;
    Value second;
};
using KeyValue = Pair<int, string>;


template<typename T>
concept AnyContainer = requires(T t)
{
    t.begin();
    t.end();
    t.size();
};


// Any one of the 4 lines are valid concept usage.
template<AnyContainer Container> void print_container(const Container& c)
//template<typename Container> requires(AnyContainer<Container>) void print_container(const Container& c)
//template<typename Container> void print_container(const Container& c) requires(AnyContainer<Container>)
//void print_container(const AnyContainer auto& c)
{
    for(const auto& item : c)
        cout << item << ", ";
    cout << endl;
}

void print_container(const vector<KeyValue>& c)
{
    for(const auto& item : c)
    {
        const auto& key = item.first;
        const auto& value = item.second;

        cout << "[" << key << ", " << value << "], ";
    }
    cout << endl;
}

//using size_t = unsigned long int;

template<size_t N>
void print_container(const array<int, N>& a)
{
    cout << "array" << endl;
}


int main(int argc, char* argv[])
{

    auto p = KeyValue{10, "ten"};
    auto vp = vector<KeyValue>{
        {10, "ten"},
        {11, "eleven"},
        {12, "twelve"}
    };

    auto m1 = map<int, string>{
        {10, "ten"},
        {11, "eleven"},
        {12, "twelve"}
    };

    auto m2 = map<string, int>();
//    {
//        {"ten", 10},
//        {"eleven", 11},
//        {"twelve", 12}
//    };

//    for(auto iter=m1.begin(); iter!=m1.end(); ++iter)
//    {
//        const auto& item = *iter; // item is of type pair<int, string>
//        const auto& key = item.first;
//        const auto& value = item.second;
//        m2[value] = key;
//    }

//    for(auto iter=m1.begin(); iter!=m1.end(); ++iter)
//    {
//        const auto& [key, value] = *iter; // structured-binding
//        m2[value] = key;
//    }

    for(const auto& [key, value] : m1)
        m2[value] = key;

    cout << m2["twelve"] << endl;

    auto v = vector<int>{1, 2, 3};
    v.push_back(4);
    auto a = array<float, 3>{10.0f, 20.0f, 30.0f};
    auto vg = vector<Gender>{Male, Female, Female};
    print_container(v);
    print_container(a);
    print_container(vg);
    print_container(vp);

//    print_container(10);

    return 0;
}
