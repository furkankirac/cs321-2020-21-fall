// global scope, local scope
int i=1;

// free-function?

// class/struct? object? ------> type? instance?

// ctor of a primitive type
// ctor of a complex type (struct)

// write a ctor of a struct instance as a free function (imperative programming paradigm)
// write a ctor of a struct instance as a member function (OOP paradigm)

// allocate memory at run-time (dynamic memory allocation)
// free memory at run-time

// write a dtor as a free function (imperative programming paradigm)
// write a dtor as a member function (OOP paradigm)

// member variables = attributes (OOP)
// static attributes
// static variables

#include <iostream>

void do_smt()
{
    std::cout << "Hi!" << std::endl;
}

// "construction" word is equivalent to "instantiation" in this lecture

// primitive types: int, float, char, short, long, double, ...
//int i;

int main(int argc, char* argv[])
{
    struct Employee
    {
        int age;
        float salary;
        char name[20];
    };

    Employee employee;
    Employee employee2;

    int i=2;
    int j=100;

    employee.age = 25;
    employee2.age = 30;

    // pointer (*)?
    // const keyword and const correctness in C++
    // east and west constness in C++
    const int * const ptr = &j; // east const

//    *ptr = 20;
//    ptr = &i;
//    ptr = &i;
//    *ptr = 500;

//    std::cout << *ptr << std::endl;

    std::cout << "i=" << i << std::endl;
    std::cout << "j=" << j << std::endl;
    std::cout << "address of local i is: " << ptr << std::endl; // stack memory
    std::cout << "address of global i is: " << &::i << std::endl; // non-stack memory
    do_smt();

    return 0;
}

