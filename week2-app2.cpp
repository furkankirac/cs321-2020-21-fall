// class/struct? object? ------> type? instance?

// ctor of a primitive type
char k = 'A';

// allocate memory at run-time (dynamic memory allocation)
// free memory at run-time

// write a dtor as a free function (imperative programming paradigm)
// write a dtor as a member function (OOP paradigm)

// member variables = attributes (OOP)
// static attributes

// static variables covered in next lecture

#include <iostream>

// ctor of a complex type (struct)
struct Student
{
    static int count;

    char* name;
    int age;
    char* origin;
    float gpa;

    // member-function now constructor (same name with Type)
    // write a ctor of a struct instance as a member function (OOP paradigm)
    Student(const char* name_, int age_, const char* origin_, float gpa_)
    {
        count++;
        name = new char[strlen(name_)+1];
        strcpy(name, name_);
        age = age_;

        origin = new char[strlen(origin_)+1];
        strcpy(origin, origin_);
        gpa = gpa_;
    }

    ~Student()
    {
        count--;
    }

    void destruct()
    {
        delete[] this->name;
        delete[] this->origin;
    }
};

int Student::count = 0;

// write a ctor of a struct instance as a free function (imperative programming paradigm)
// free-function
void student_ctor(Student& s, const char* name_, int age_, const char* origin_, float gpa_)
{
    strcpy(s.name, name_);
    s.age = age_;
    strcpy(s.origin, origin_);
    s.gpa = gpa_;
}


int main(int argc, char* argv[])
{
    {
        Student s1("Furkan", 42, "Istanbul", 3.0f);
        std::cout << "Student instance count = " << Student::count << std::endl;

        Student s2("Hasan", 37, "Bursa", 3.2f);
        std::cout << "Student instance count = " << Student::count << std::endl;
    //    student_ctor(s1, "Furkan", 42, "Istanbul", 3.0f);
    //    student_ctor(s2, "Hasan", 37, "Bursa", 3.2f);

        std::cout << s1.name << std::endl;
        std::cout << s2.name << std::endl;

        s1.destruct();
    }

    std::cout << "Student instance count = " << Student::count << std::endl;

    return 0;
}

