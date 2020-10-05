// Major Concepts to touch:

// Lecture contents will be available in the LMS
// code will be available in https://github.com/furkankirac

// History of C++
// Core language + Standard Library
// Standard Library: libstdc++, libc++
// CMake: is important, not very likable, but nothing better than it right now :(

// Imperative-Programming paradigm
// Object-Oriented-Programming paradigm
// Functional-Programming paradigm
// Generic-Programming paradigm

// Compile-time vs run-time parameters

// Midterm Exam 1 (25%)
// A difficult problem to be solved in 1-day time (open-book)
// Your unique solution is required

// Midterm Exam 2 (35%)
// A difficult problem to be solved in 1-day time (open-book)
// Your unique solution is required

// Final Exam (40%)
// A difficult problem to be solved in 1-day time (open-book)
// Your unique solution is required

// Thursdays are Lab Sections

// Will use:
//   Compiler: Clang 10+ and C++20 standard.
//   You can use one of Clang, GCC, MSVC compilers, and any editor of your choice.
//   However, I would highly suggest you to use Qt Creator if not familiar with C++.
//   Editor: Qt Creator 4.13+. Why? Lightweight, very nicely supports CMake.

// COMPILER CONFORMANCE: https://en.cppreference.com/w/cpp/compiler_support

// C and C++ have smt. called preprocessor

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace std;
    //namespace std
    cout << "Hello World" << endl;
    cout << "I have been supplied " << argc << " many arguments." << endl;
    cout << "1st argument is " << argv[0] << endl;
    for(int i=0; i<argc; i++)
    {
        cout << argv[i] << endl;
    }
    return 0;
}
