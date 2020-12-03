#include <iostream>
#include <string>
#include <vector>

using namespace std; // not a good idea, in complicated projects always use this in a local scope

template<typename Container>
auto filter(const Container& container, auto func)
{
    auto c = Container();
    for(const auto& item : container)
        if(func(item))
            c.push_back(item);
    return c;
}

auto contains(const auto& container, auto func)
{
    for(const auto& item : container)
        if(func(item))
            return true;

    return false;
}

enum LetterGrade { A, A_minus, B_plus, B, B_minus, C_plus, C, C_minus, D_plus, D, F };

using CourseCode = string;
struct Course
{
    CourseCode code;
    unsigned short credit; // unsigned short int
};
using Courses = vector<Course>;

struct CourseGrade
{
    CourseCode code;
    LetterGrade letter_grade;
};

using CourseGrades = vector<CourseGrade>;
struct Student
{
    string name;
    CourseGrades course_grades;

    auto num_taken_courses() const { return course_grades.size(); }
    bool has_taken_course(CourseCode code) const
    {
        return contains(course_grades, [&](const CourseGrade& cg) {
            return cg.code == code;
        });
    }
};

using Students = vector<Student>;

auto courses = Courses{
    { "CS201", 6 },
    { "CS321", 6 },
    { "CS401", 4 },
    { "CS402", 4 }
};

auto students = Students{
    { "Ali", { {"CS201", A_minus}, {"CS401", B_minus} } },
    { "Veli", { {"CS201", A}, {"CS321", B_plus}, {"CS401", C_plus} } },
    { "Mehmet", { {"CS201", B_plus} } },
};


void print(const Students& students)
{
    for(const auto& s : students)
        cout << s.name << endl;
}

int main(int, char*[])
{
    // use filter algorithm on students for filtering the students
    // who has taken CS401 course before, then write the names of the students with print(v1)
    for(const auto& course : courses)
    {
        cout << "Course Code is " << course.code << endl;
        auto v1 = filter(students, [&](const Student& s) {
            return s.has_taken_course(course.code);
        });
        print(v1);
    }

    // use filter algorithm on students for filtering the students
    // who has taken at least 3 courses before, then write the names of the students with print(v2)
    auto v2 = filter(students, [](const Student& s) {
        return s.num_taken_courses() >= 3;
    });
    print(v2);

    return 0;
}
