// Radian/Degree example
// converting constructors
// pass by value, pass by reference, pass by constant reference
// implicit/explicit constructors
// user-defined literals
// operator+ overload for Radian/Degree

#include <iostream>

const double PI = 3.1459;

struct Radian;

struct Degree
{
    double angle;

    Degree(double angle) : angle(angle) { }
    Degree(const Radian& radian);
};

struct Radian
{
    double angle;

    Radian(double angle) : angle(angle) { }
    Radian(const Degree& degree) : angle(degree.angle/180.0*PI) { }

    auto operator+(const Radian& right)
    {
        return Radian(angle + right.angle);
    }
};

Degree::Degree(const Radian& radian) : angle(radian.angle/PI*180.0) { }


void print(const Radian& value)
{
    std::cout << "Radian = " << value.angle << std::endl;
}

void print(const Degree& value)
{
    std::cout << "Degree = " << value.angle << std::endl;
}

auto operator"" _degree(long double value)
{
    return Degree(value);
}

auto operator"" _radian(long double value)
{
    return Radian(value);
}

//auto operator+(const Radian& left, const Radian& right)
//{
//    return Radian(left.angle + right.angle);
//}


int main(int argc, char* argv[])
{
    auto angle1 = Radian(PI);
    auto angle2 = Degree(180.0);

    auto angle3 = 90.0_degree;
    auto angle4 = 6.28_radian;

    print(angle1);
//    print(angle2); // implicitly creating a Radian from a Degree by compiler
    print(Radian(angle2));
    print(angle3);
    print(angle4);

    auto angle1_4 = angle1 + angle4;
    print(angle1_4);

    auto angle1_2 = angle1 + angle2; //implicit conversion here for angle2
//    auto angle1_2 = operator+(angle1, angle2); // free-function only call
//    auto angle1_2 = angle1.operator+(angle2); // member-function only call
    print(angle1_2);

    return 0;
}
