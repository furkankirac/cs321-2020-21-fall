// universal construction:
//   stricter construction with {} instead of (),
//   also initializer_list support
//   designated initializers
// iterators and range-for-loop
// "transform" algorithm with function pointers
// encapsulating functions:
//   functions themselves (with func pointers),
//   function objects,
//   lambda functions

#include <iostream>
#include <vector>

using namespace std;

struct Student
{
    float gpa = 0.0f;
    int age = 18;
//    vector<char> name;

    void print() const
    {
        cout << age << "," << gpa << endl;
    }
};

void print(const vector<int>& a)
{
//    auto size = a.size();
//    for(auto i=0; i<size; ++i)
//        cout << a[i] << " ";
//    cout << endl;

////    vector<int>::const_iterator it = a.begin();
//    for(auto it = a.begin(); it != a.end(); ++it)
//    {
//        const auto& item = *it;
//        cout << item << " ";
//    }
//    cout << endl;

    for(const auto& item : a)
        cout << item << " ";
    cout << endl;

}

int main(int argc, char* argv[])
{
    auto student = Student{.gpa=4.0f, .age=20};
    student.print();

//    auto v = vector<int>(3); // inits a vector with 3 elements, the elements are default constructed
//    auto v = vector<int>{3}; // inits a vector with 1 element, the element being 3 itself
    auto v = vector<int>{10, 20, 30};
//    v[0] = 10;
//    v[1] = 20;
//    v[2] = 30;
    print(v);

    return 0;
}
