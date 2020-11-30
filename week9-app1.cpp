// improve midterm solution:
//  use auto arguments, if constexpr, concepts, requires expression/clause...

// lifting a function (higher order functions):
//  a function returning a function object: delays function use

// in search of a simpler and more understandable generic way of writing code
//  the dance of OOP, FP and GP paradigms

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>

enum Gender { Female, Male };

struct Employee
{
    std::string name;
    Gender gender;
    int age;
    float salary;
};

// a concept required to distinguish a typename if it is a container or not
// any type T with whose instance a we can safely call a.begin(), a.end(), a.size() is a container
template<typename T>
concept AnyContainer = requires(T a) {
    a.begin();
    a.end();
    a.size();
};

template<typename T>
concept AnyMap = requires(T a) {
    AnyContainer<T>;
    a.begin()->first;
    a.begin()->second;
};

// algorithms

template<typename Container>
auto filter(const Container& container, auto func)
{
    auto c = Container();
    for(const auto& item : container)
        if(func(item))
            c.push_back(item);
    return c;
}

auto group_by(const auto& container, auto func)
{
    using Key = decltype(func(*container.begin()));
    using Value = std::vector<typename std::remove_reference<decltype(*container.begin())>::type>;
    auto m = std::map<Key, Value>();
    for(const auto& item : container)
        m[func(item)].push_back(item);
    return m;
}

template<typename Container>
auto transform(const Container& container_, auto func)
{
    if constexpr(AnyMap<Container>)
    {
        using Pair = decltype(func(*container_.begin()));
        using NewKey = decltype(Pair().first);
        using NewValue = decltype(Pair().second);

        auto container = std::map<NewKey, NewValue>();
        for(const auto& item : container_)
        {
            auto pair = func(item);
            container[pair.first] = pair.second;
        }
        return container;
    }
    else
    {
        auto container = container_;
        for(auto& item : container)
            item = func(item);
        return container;
    }
}

// Reverse algorithm for any type of containers
//template<typename Container>
//template<AnyContainer Container>
auto reverse(const AnyContainer auto& container)
{
    auto c = container;
    auto sz = c.size(); // size_t
    for(auto i=size_t{}; i<sz/2; ++i)
    {
        auto t = c[i];
        c[i] = c[sz-i-1];
        c[sz-i-1] = t;
    }
    return c;
}


// make Employee printable to the console
std::ostream& operator<<(std::ostream& s, const Employee& e)
{
    std::cout << e.name << ", " << (e.gender==Female ? "Female" : "Male") << ", " << e.age << ", " << e.salary << "TL";
    return s;
}

// print function overload set starts here

// template of print functions suitable for any kind of type
template<typename T>
void print(const T& value)
{
    if constexpr(AnyMap<T>)
    {
        for(const auto& [key, val] : value)
        {
            std::cout << "<" << key << ">: ";
            print(val);
        }
    }
    else if constexpr(AnyContainer<T>)
    {
        auto sz = value.size();
        auto i = decltype(sz)(0);
        for(const auto& item : value)
        {
            std::cout << "[" << item << "]";
            if(i++ != sz-1)
                std::cout << "; ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << value << std::endl;
    }

}

// define a dummpy Print type. Instantiate a variable of it, and call it PRINT
// PRINT variables only specialty is that its type is Print.
// We will use its type for distinguishing it in different scenarios, as shown in below code
struct Print { };
auto PRINT = Print();

// if | (pipe) operator is seen between any type T that suits AnyContainer concept and
// a variable of type Print (an example is PRINT variable)
template<AnyContainer T> void operator|(const T& c, Print) { print(c); }

// if & operator is seen between a type T that suits AnyContainer concept and any function object
template<AnyContainer T, typename Lambda> auto operator&(const T& c, Lambda lambda) { return filter(c, lambda); }

// if | (pipe) operator is seen between a type T that suits AnyContainer concept and any function object
template<AnyContainer T, typename Lambda> auto operator|(const T& c, Lambda lambda) { return transform(c, lambda); }

// if - operator is seen before a variable of type that suits AnyContainer concept
template<AnyContainer T> auto operator-(const T& c) { return reverse(c); }

//auto get_name_original(const auto& e) { return e.name; }

auto get_name() { return [](const auto& e) { return e.name; }; }
auto get_salary() { return [](const auto& e) { return e.salary; }; }
auto get_gender() { return [](const auto& e) { return e.gender; }; }

auto lt(auto value) { return [value](auto v) { return v < value; }; }
auto eq(auto value1) { return [value1](auto value2) { return value1 == value2; }; }

auto both_of(auto f1, auto f2) {
    return [f1, f2](const auto& item) {
        return f1(item) && f2(item);
    };
}

auto operator&&(auto f1, auto f2) {
    return both_of(f1, f2);
}

auto compose(auto f, auto g) // FoG
{
    return [f, g](auto x) {
        return g(f(x));
    };
}

auto operator |(auto f, auto g) { return compose(f, g); }

int main(int, char* [])
{
    auto employees = std::vector<Employee>{
        {"Fatih", Male, 35, 8500},
        {"Elif", Female, 28, 6350},
        {"Erkin", Male, 43, 9500},
        {"Mehmet", Male, 46, 10500},
        {"Melis", Female, 48, 12500},
        };

    auto e = employees[0];
//    auto func = get_name();
//    std::cout << func(e) << std::endl;

//    auto lt8000 = lt(8000);
//    auto sal = get_salary()(e);
//    if(lt8000(sal))
//        std::cout << "Less than 9000!" << std::endl;


    std::cout << "Female employees who take less salary than 9000TL:" << std::endl;
//    print(filter(employees, (get_salary()|lt(9000) && (get_gender()|eq(Female)) )));
    employees & (get_salary()|lt(9000) && (get_gender()|eq(Female))) | PRINT;
    print(filter(employees, [](const Employee& e) { return e.salary < 9000 && e.gender == Female; }));
    // [Elif, Female, 28, 6350TL]

//    // Q6a) (15pts) Create a group_by algorithm that can group elements of a container by a specific criterion
//    // Q6b) (5pts) Group employees by age ranges of 10 year increments by filling in lambda_group below
//    // Q6c) (5pts) Make the grouped result printable via print(grouped) as below
//    std::cout << "Employees grouped by age ranges of 10 year increments:" << std::endl;
//    auto lambda_group = [](const Employee& e) {
//        auto a = e.age/10*10; // note: division of integer truncates the result.
//        auto b = a+9;
//        return std::to_string(a) + ".." + std::to_string(b);
//    };
//    auto grouped = group_by(employees, lambda_group);
//    print(grouped);
//    // <20..29>: [Elif, Female, 28, 6350TL]
//    // <30..39>: [Fatih, Male, 35, 8500TL]
//    // <40..49>: [Erkin, Male, 43, 9500TL]; [Mehmet, Male, 46, 10500TL]; [Melis, Female, 48, 12500TL]

//    // Q7a) (10pts) Create a transform algorithm that can work on "grouped" variable.
//    // Q7b) (5pts) Write necessary transformation lambda for aggregating each group's element count.
//    // Q7c) (5pts) Make the grouped and transformed result printable via print(grouped_transformed) as below
//    std::cout << "Number of employees available in age ranges of 10 year increments:" << std::endl;
//    auto lambda_transform = []<typename T>(const T& pair) {
//        using Key = decltype(pair.first);
//        using Value = size_t;
//        return std::pair<Key, Value>{pair.first, pair.second.size()};
//    };
//    auto grouped_transformed = transform(grouped, lambda_transform);
//    print(grouped_transformed);
//    // <20..29>: 1
//    // <30..39>: 1
//    // <40..49>: 3

//    // Q8) (10pts) Make the below code work as the same as Q7's code block
//    std::cout << "Number of employees available in age ranges of 10 year increments (again):" << std::endl;
//    grouped | lambda_transform | PRINT;
//    // <20..29>: 1
//    // <30..39>: 1
//    // <40..49>: 3

//    // Q9) (5pts) Make below line work
//    std::array<int, 3>{10, 20, 30} | [](int a) { return a*a; } | PRINT;
//    // [100]; [400]; [900]

//    // Q10) Overload "operator-" to get the reverse of passed container
//    // Q10a) (5pts) Make it work with array containers with the result pipable to PRINT as below
//    // Q10b) (5pts) Make it work with other containers with the result pipable to PRINT as below
//    -std::array<float, 4>{1.1, 2.2, 3.3, 4.4} | PRINT;
//    // [4.4]; [3.3]; [2.2]; [1.1]
//    -std::vector<float>{1.1, 2.2, 3.3, 4.4} | PRINT;
//    // [4.4]; [3.3]; [2.2]; [1.1]

    return 0;
}

