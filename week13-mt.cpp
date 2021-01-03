// StudentID: xxxxxxxx, Name: AAA BBB CCC

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

// CAREFUL!
// + Do not use "using namespace std;".
//   Always write std:: explicitly in your solutions if you want to use standard lib.
// + std::string also has a begin(), end(), size() methods. std::string is actually a container of chars.
// + transform algorithm required in this exam is slightly more generic
//   it can not only change container's values but can also change the type to a new type
//   i.e. std::vector<int>{10} may be transformed to std::vector<std::string>{"11"}
//   (if the supplied lambda was: increment by one, convert to a string and return it)
// + It is enough for this exam to support only std::vector as container.
// + You can also capture lambdas with "const auto& lambda" instead of "auto lambda".
//   It won't be a problem for this exam.
// + Exam starts below. Provided code CANNOT be changed. Just fill in the necessary gaps to produce the
//   wanted outcome (output).

// + Type aliases and traits for easy usage of std classes are declared for you as shown below.
using String = std::string;
template<typename ... Ts> using Vector = std::vector<Ts...>;
template<typename ... Ts> using Tuple = std::tuple<Ts...>;

template<typename T>      struct is_tuple                    { static const bool value = false; };
template<typename ... Ts> struct is_tuple<std::tuple<Ts...>> { static const bool value = true; };

// custom user literal _s is declared for easy std::string constant usage such as "hello"_s
auto operator"" _s(const char* str, size_t) { return std::string(str); }

// Distinct new classes are derived from already available base classes for you
struct Integer
{
    int value;
    Integer(int value) : value(value) { }
};

// A simple struct and its container is declared in a generic way that has 4 dimensions
struct Name : String { using String::String; Name(const String& s) : String(s) {};};
struct Surname : String { using String::String; Surname(const String& s) : String(s) {};};
struct BirthYear : Integer { using Integer::Integer; };
struct DeathYear : Integer { using Integer::Integer; };
using Scientist = Tuple<Name, Surname, BirthYear, DeathYear>;
using Scientists = Vector<Scientist>;

// A simple struct and its container is declared in a generic way that has 2 dimensions
struct FullName : String { using String::String; FullName(const String& s) : String(s) {}; };
struct Url : String { using String::String; Url(const String& s) : String(s) {}; };
using Link = Tuple<FullName, Url>;
using Links = Vector<Link>;

// Declare necessary concepts, operator overloads, algorithms, their higher order versions, etc.
// for to make below code execute and produce the wanted output exactly as described.
// WRITE YOUR CODE HERE

template<typename T> concept IsString = requires(T t) { t.c_str(); };
template<typename T> concept IsContainer = !IsString<T> && requires(T t) { t.begin(); t.end(); t.size(); };
template<typename T> concept IsTuple = is_tuple<T>::value;
template<typename T> concept HasValue = requires(T t) { t.value; };

template<typename Left, typename Right>
auto operator|(const Left& left, const Right& right)
{
    if constexpr(IsContainer<Left> || IsTuple<Left> || IsString<Left>)
        return right(left);
    else
        return [=](const auto& value) { return right(left(value)); };
}

// shortcut for std::get usage
template<typename T>
auto get(const auto& a) { return std::get<T>(a); };

// when get is used in a context in which from where to get is not available yet
template<typename T>
auto get() { return [](const auto& a) { return std::get<T>(a); }; }

std::ostream& operator<<(std::ostream& s, const HasValue auto& t) { s << t.value; return s; }

template<typename ... Ts>
std::ostream& operator<<(std::ostream& s, const Tuple<Ts...>& t)
{
    ((s << "(" << get<Ts>(t) << ") "), ...);
    return s;
}

template<typename T>
void print(const T& value)
{
    if constexpr(IsContainer<T>)
    {
        for(const auto& item : value)
            std::cout << item << std::endl;
    }
    else
    {
        std::cout << value << std::endl;
    }
    std::cout << std::endl;
}

auto printer(const String& title = "")
{
    return [=](const auto& value) {
        if(!title.empty())
            std::cout << title << std::endl;
        print(value);
        return value;
    };
}

template<typename ... AttribTypes>
auto select(const IsTuple auto& tpl)
{
    return make_tuple(get<AttribTypes>(tpl)...);
    //return Tuple<AttribTypes...>(get<AttribTypes>(tpl)...);
};

template<typename ... AttribTypes>
auto select(const IsContainer auto& container)
{
    using ElemType = decltype(select<AttribTypes...>(*container.begin()));
    auto c = std::vector<ElemType>();
    for(const auto& tpl : container)
        c.push_back(select<AttribTypes...>(tpl));
    return c;
};

template<typename ... AttribTypes>
auto select()
{
    return [=](const auto& item) {
        return select<AttribTypes...>(item);
    };
}

template<IsContainer Container>
auto where(const Container& container, auto lambda)
{
    auto c = Container();
    for(const auto& item : container)
        if(lambda(item))
            c.push_back(item);
    return c;
};

auto where(auto lambda)
{
    return [=](const auto& container) {
        return where(container, lambda);
    };
}

template<IsContainer Container>
auto transform(const Container& container, auto lambda)
{
    using NewItem = decltype(lambda(*container.begin()));
    auto c = Vector<NewItem>();
    for(const auto& item : container)
        c.push_back(lambda(item));
    return c;
};

auto transform(auto lambda)
{
    return [=](const auto& container) {
        return transform(container, lambda);
    };
};

template<typename T>
auto equal_to(const T& value)
{
    return [=](const T& item) { return value == item; };
}

template<typename ... As, typename ... Bs>
auto cartesian(const Vector<Tuple<As...>>& c1, const Vector<Tuple<Bs...>>& c2)
{
    using NewTuple = Tuple<As..., Bs...>;
    auto c = Vector<NewTuple>();
    for(const auto& i1 : c1)
        for(const auto& i2 : c2)
            c.push_back(std::make_tuple(get<As>(i1)..., get<Bs>(i2)...));
    return c;
}

auto eval_namesurname(const auto& tpl) {
    return FullName{get<Name>(tpl) + " " + get<Surname>(tpl)};
};
auto eval_namesurname() {
    return [=](const auto& tpl) {
        return eval_namesurname(tpl);
    };
};

// Below are written for you and shall not be changed.
int main(int, char* [])
{
    auto scientists = Scientists{
        {"Charles", "Babbage", 1791, 1871},
        {"Ada", "Lovelace", 1815, 1852},
        {"Alan", "Turing", 1912, 1954},
        };

    auto links = Links{
        {"Ada Lovelace", "https://en.wikipedia.org/wiki/Ada_Lovelace"},
        {"Alan Turing", "https://en.wikipedia.org/wiki/Alan_Turing"},
        };

    "CS321 Midterm 2 begins:"_s | printer();

    print("Q1 - Print 'scientists' and 'links' containers");
    scientists | printer("Scientists");
    links | printer("Links");

    *scientists.begin()
        | eval_namesurname()
        | printer("Q2 - Write a lambda that returns 'Name' and 'Surname' concatenated with a space in between");

    scientists
        | transform(eval_namesurname())
        | printer("Q3 - Transform tuples with a new one with 'Name Surname' concatenated");

    cartesian(scientists, links)
        | printer("Q4 - Cartesian Product of two containers")
        | where([=](const auto& tpl) { return eval_namesurname()(tpl) == get<FullName>(tpl); })
        | printer("Q5 - Filter the elements where evaluated name surname is equal to the full name")
        | select<Url, FullName, BirthYear, DeathYear>()
        | printer("Q6 - Select Url, FullName, BirthYear, DeathYear fields in that order");

    scientists
        | where(get<Name>() | equal_to("Ada"_s))
        | printer("Q7 - Filter the elements where Name field is equal to 'Ada'");

    return 0;
}
