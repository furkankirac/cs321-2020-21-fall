// std::tuple, is_tuple, is_tuple_v
// std::get<T>, std::get<index>
// tuple_element_t<index, T>
// tuple_size_v<T>

// type aliasing vs creating a new struct by inheriting
// std::pair<int, int> ---> use for representing a range of dates

// writing a generic Concept for detecting all kinds of lambdas is not possible
// you can design your own Function Object base class and write all lambdas in the form of function objects
//  that inherit your base class, and check base class availability as a parent
//  however, not fancy.
//  So, in generic programming you generally use concepts to constrain to the types that are not lambdas
//   and everything else is considered to be lambda. Hence, typename is used to represent lambdas.

#include <iostream>
#include <string>
#include <tuple>

auto operator"" _s(const char* str, size_t) { return std::string(str); }

using String = std::string;

//using Name = std::string;
//using Surname = std::string;
//using Gpa = float;
struct Name : String { using String::String; };
struct Surname : String { using String::String; };
struct Gpa
{
    float value;
    Gpa(float value) : value(value) { }
};
struct Age
{
    short value;
    Age(short value) : value(value) { }
};

//using Age = short;

struct Student
{
    Name name;
    Surname surname;
    Gpa gpa;
    Age age;
};

template<typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;
};

//template<typename T1, typename T2, typename T3>
//struct ThreeThings
//{
//    T1 first;
//    T2 second;
//    T3 third;
//};

template<typename ...>
struct TypeDebug;


template<typename T> struct is_tuple                             { static const bool value = false; };
template<typename ... Ts> struct is_tuple< std::tuple<Ts...> >   { static const bool value = true; };

template<typename T>
concept IsTuple = is_tuple<T>::value;


std::ostream& operator<<(std::ostream& str, const Student& stu)
{
    str << stu.name << ", " << stu.gpa.value << std::endl;
    return str;
}

int main(int, char* [])
{
    auto p = Pair<int, std::string>{10, "ten"};

    auto s = Student{"Ali", "Kanik", 4.0f, 22};
    std::cout << s << std::endl;
    std::cout << s.name << std::endl;

    using TUPLE = std::tuple<Name, Surname, Gpa, Age>;
    auto tpl = TUPLE("Ali", "Kanik", 4.0f, 22);
//    auto tpl = std::make_tuple("Ali", 4.0f, 22, 3.5f);

//    std::cout << "!" << is_tuple<Student>::value << std::endl;

    // get the number of dimensions of a TUPLE type at compile-time
    std::cout << std::tuple_size_v<TUPLE> << std::endl;

//    TypeDebug< std::tuple_element_t<3, TUPLE> > a;

//    std::cout << std::get<Surname>(tpl) << std::endl;
//    std::cout << std::get<2>(tpl) << std::endl;

    return 0;
}
