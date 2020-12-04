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

// algorithms

template<typename Container, typename Func>
auto filter(const Container& container, Func func)
{
    auto c = Container();
    for(const auto& item : container)
        if(func(item))
            c.push_back(item);
    return c;
}

template<typename Container, typename Func>
auto group_by(const Container& container, Func func)
{
    using Key = decltype(func(*container.begin()));
    using Value = std::vector<typename std::remove_cvref<decltype(*container.begin())>::type>;
    auto m = std::map<Key, Value>();
    for(const auto& item : container)
        m[func(item)].push_back(item);
    return m;
}

// Most generic definition of transform algorithm: this is chosen if a more special transform does not suit to your case
template<typename Container, typename Func>
auto transform(Container container, Func func)
{
    for(auto& item : container)
        item = func(item);
    return container;
}

// Special transform algorithm suitable for std::map type containers
template<typename Key, typename Value, typename Func>
auto transform(const std::map<Key, Value>& container, Func func)
{
    using Pair = decltype(func(*container.begin()));
    using NewKey = decltype(Pair().first);
    using NewValue = decltype(Pair().second);

    auto c = std::map<NewKey, NewValue>();
    for(const auto& item : container)
    {
        auto pair = func(item);
        c[pair.first] = pair.second;
    }
    return c;
}

// Reverse algorithm for any type of containers
template<typename Container>
//template<AnyContainer Container>
auto reverse(const Container& container)
{
    auto c = container;
    auto sz = c.size();
    for(auto i=0; i<sz/2; ++i)
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
    std::cout << value << std::endl;
}

// template of different print functions suitable for container types
// this takes precedence to the generic print template above when specific criteria match
// (if it is suitable to AnyContainer concept)
template<AnyContainer Container>
void print(const Container& c)
{
    auto sz = c.size();
    auto i = decltype(sz)(0);
    for(const auto& item : c)
    {
        std::cout << "[" << item << "]";
        if(i++ != sz-1)
            std::cout << "; ";
    }
    std::cout << std::endl;
}

// template of different print functions suitable for all different types of std::map containers
// if passed argument matches std::map<Key, Value> pattern this one takes precedence to the above versions
template<typename Key, typename Value>
void print(const std::map<Key, Value>& m)
{
    for(const auto& [key, value] : m)
    {
        std::cout << "<" << key << ">: ";
        print(value);
    }
}

// define a dummy Print type. Instantiate a variable of it, and call it PRINT
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

// some helper structs for removing constness of different types
template<typename T> struct remove_const          { using type = T; };
template<typename T> struct remove_const<const T> { using type = T; };

int main(int, char* [])
{
    auto employees = std::vector<Employee>{
        {"Fatih", Male, 35, 8500},
        {"Elif", Female, 28, 6350},
        {"Erkin", Male, 43, 9500},
        {"Mehmet", Male, 46, 10500},
        {"Melis", Female, 48, 12500},
        };

    // Q1) (5pts) Make employee directly sendable to the console
    std::cout << "First Employee:" << std::endl << employees[0] << std::endl;
    // Fatih, Male, 35, 8500TL

    // Q2) (5pts) Create a print overload that can print "employees" variable
    std::cout << "All Employees:" << std::endl;
    print(employees);
    // [Fatih, Male, 35, 8500TL]; [Elif, Female, 28, 6350TL]; [Erkin, Male, 43, 9500TL]; [Mehmet, Male, 46, 10500TL]; [Melis, Female, 48, 12500TL]

    auto age_thresh = 40;

    // Q3) (5pts) Create a filter overload that can work with any kind of containers. Make it work with "employees"
    std::cout << "Employees older than 40 years old:" << std::endl;
    auto lambda_filter = [&age_thresh](const Employee& e) { return e.age > age_thresh; };
    auto age_gt_40 = filter(employees, lambda_filter);
    print(age_gt_40);
    // [Erkin, Male, 43, 9500TL]; [Mehmet, Male, 46, 10500TL]; [Melis, Female, 48, 12500TL]

    // Q4a) (5pts) Apply filter to a container by & operator
    // Q4b) (5pts) Send container to console by piping it to PRINT with | operator.
    age_thresh = 45;
    std::cout << "Employees older than 45 years old (again in functional composition):" << std::endl;
    employees & lambda_filter | PRINT;
    // [Mehmet, Male, 46, 10500TL]; [Melis, Female, 48, 12500TL]

    // Q5) (5pts) Make below code work.
    std::cout << "Female employees who take less salary than 9000TL:" << std::endl;
    print(filter(employees, [](const Employee& e) { return e.salary < 9000 && e.gender == Female; }));
    // [Elif, Female, 28, 6350TL]

    // Q6a) (15pts) Create a group_by algorithm that can group elements of a container by a specific criterion
    // Q6b) (5pts) Group employees by age ranges of 10 year increments by filling in lambda_group below
    // Q6c) (5pts) Make the grouped result printable via print(grouped) as below
    std::cout << "Employees grouped by age ranges of 10 year increments:" << std::endl;
    auto lambda_group = [](const Employee& e) {
        auto a = e.age/10*10; // note: division of integer truncates the result.
        auto b = a+9;
        return std::to_string(a) + ".." + std::to_string(b);
    };
    auto grouped = group_by(employees, lambda_group);
    print(grouped);
    // <20..29>: [Elif, Female, 28, 6350TL]
    // <30..39>: [Fatih, Male, 35, 8500TL]
    // <40..49>: [Erkin, Male, 43, 9500TL]; [Mehmet, Male, 46, 10500TL]; [Melis, Female, 48, 12500TL]

    // Q7a) (10pts) Create a transform algorithm that can work on "grouped" variable.
    // Q7b) (5pts) Write necessary transformation lambda for aggregating each group's element count.
    // Q7c) (5pts) Make the grouped and transformed result printable via print(grouped_transformed) as below
    std::cout << "Number of employees available in age ranges of 10 year increments:" << std::endl;
    auto lambda_transform = [](const auto& pair) {
        using Key = typename remove_const<decltype(pair.first)>::type;
        using Value = size_t;
        return std::pair<Key, Value>{pair.first, pair.second.size()};
    };
    auto grouped_transformed = transform(grouped, lambda_transform);
    print(grouped_transformed);
    // <20..29>: 1
    // <30..39>: 1
    // <40..49>: 3

    // Q8) (10pts) Make the below code work as the same as Q7's code block
    std::cout << "Number of employees available in age ranges of 10 year increments (again):" << std::endl;
    grouped | lambda_transform | PRINT;
    // <20..29>: 1
    // <30..39>: 1
    // <40..49>: 3

    // Q9) (5pts) Make below line work
    std::array<int, 3>{10, 20, 30} | [](int a) { return a*a; } | PRINT;
    // [100]; [400]; [900]

    // Q10) Overload "operator-" to get the reverse of passed container
    // Q10a) (5pts) Make it work with array containers with the result pipable to PRINT as below
    // Q10b) (5pts) Make it work with other containers with the result pipable to PRINT as below
    -std::array<float, 4>{1.1, 2.2, 3.3, 4.4} | PRINT;
    // [4.4]; [3.3]; [2.2]; [1.1]
    -std::vector<float>{1.1, 2.2, 3.3, 4.4} | PRINT;
    // [4.4]; [3.3]; [2.2]; [1.1]

    return 0;
}
