#include <iostream>
//#include <stdio.h>

void my_strcpy(char* dest_ptr, const char* src_ptr)
{
    while(*src_ptr != 0)
        *dest_ptr++ = *src_ptr++;
}

struct Employee
{
    int salary;
    int age;
    char name[20];

    Employee(int salary_, int age_, const char* name_)
    {
        salary = salary_;
        age = age_;
        my_strcpy(name, name_);
    }
};


int main(int argc, char* argv[])
{
    using namespace std;

    Employee e1(10000, 25, "Furkan");
    Employee e2(12000, 35, "Ali");

    cout << e1.name << endl;
    cout << e2.name << endl;

    return 0;
}
