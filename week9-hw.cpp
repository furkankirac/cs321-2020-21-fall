#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum LetterGrade { A, A_minus, B_plus, B, B_minus, C_plus, C, C_minus, D_plus, D, F };

using CourseCode = string;
struct Course
{
    CourseCode code;
    unsigned short credit;
};
using Courses = vector<Course>;

struct CourseGrade
{
    CourseCode code;
    LetterGrade letter_grade;
};

struct Student
{
    string name;
    vector<CourseGrade> course_grades;
};

using Students = vector<Student>;

auto courses = Courses{
    { "CS201", 6 },
    { "CS321", 6 },
    { "CS401", 4 },
    { "CS402", 4 },
};

auto students = Students{
    { "Ali", { {"CS201", A_minus}, {"CS401", B_minus} } },
    { "Veli", { {"CS201", A}, {"CS321", B_plus}, {"CS401", C_plus} } },
    { "Mehmet", { {"CS201", B_plus} } },
};


int main(int, char*[])
{
    // use filter algorithm on students for filtering the students
    // who has taken CS401 course before, then write the names of the students with print(v1)
    auto v1 = filter(students, /* fill here */);
    print(v1); // Ali, Veli

    // use filter algorithm on students for filtering the students
    // who has taken at least 3 courses before, then write the names of the students with print(v2)
    auto v2 = filter(students, /* fill here */);
    print(v2); // Veli

    return 0;
}
