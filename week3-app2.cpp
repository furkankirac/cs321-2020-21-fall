// operators and operator overloading
// function parameters: pass by value, pass by reference

// OOP:
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment (skip this for a while, related with C++ internals)
// inheritance

// auto, AAA rule (almost always auto)
// user-defined literals

#include <iostream>

struct Integer // available in Java (Java boxing/unboxing)
{
    int value;

    Integer(int value) : value(value) { }
    Integer(char c)
    {
        if(c=='Z') value = 100;
        else value = 0;
    }

    Integer(const Integer& other) : value(other.value) { } // copy ctor

    void operator=(const Integer& right) // copy assignment
    {
        value = right.value;
        std::cout << "Copy assignment" << std::endl;
    }

    void print() // member-function
    {
        std::cout << value << std::endl;
    }
};

struct FancyInteger : public Integer
{
    // opt-in for inheriting ctors, copy-ctors, copy assigment functions, ...
    using Integer::Integer; // this imports my base class's constructors

    void print_fancy() // member-function
    {
        std::cout << "----------------" << std::endl;
        std::cout << value << std::endl;
        std::cout << "----------------" << std::endl;
    }
};


Integer operator+(Integer& a, Integer b) // a is passed by reference, b is passed by value
{
    Integer result = Integer(a.value + b.value);
    a.value = 1000;
    b.value = 10000;
    return result;
}


int main(int argc, char* argv[])
{
    auto F = 3.14f;

//    auto a = 555i; // Integer(555) // possible with user defined literals

//    Integer i(5);
    auto i = Integer(5);

//    Integer j(3);
    auto j = Integer(3);

//    Integer z('Z');
    auto z = Integer('Z');

    //Integer A(i); // this is copy construction
    auto A = Integer(i);
    // ...
    // ...
    A = j; // copy assignment

    z.print();
    i.print(); //OOP style

//    Integer k = operator+(i, j);
//    Integer k = i + j;
    auto k = i + j;
    k.print();
    std::cout << "i=" << i.value << std::endl;
    std::cout << "j=" << j.value << std::endl;

//    FancyInteger f(1);
    auto f = FancyInteger(1);
    f.print_fancy();

//    operator<<(std::cout, "Hello");
//    std::cout << "Hello";

    return 0;
}
