// function pointers
// function overloading
// operators and operator overloading
// function parameters: pass by value, pass by reference

// OOP:
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment
// inheritance

// user-defined literals

// auto, AAA rule

#include <iostream>

//typedef int Integer;
using Integer = int;
Integer a = 5;

//typedef int(*Func)(int, int);
using Func = int(*)(int, int);

// function overloading: two add functions, but actually they are completely different functions
int add(int a, int b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }

int multiply(int a, int b) { return a*b; }
int run(int a, int b, Func func) { return func(a, b); }

int main(int argc, char* argv[])
{
//    int(*func)(int, int);
    Func func;
    func = &add;

    int addition = run(10, 5, &add);

    int r1 = add(10, 20);
    int r2 = add(100, 200, 300);
    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;

//    int addition = add(10, 5);

    int product = run(10, 5, &multiply);
    std::cout << addition << std::endl;
    std::cout << product << std::endl;
    return 0;
}
