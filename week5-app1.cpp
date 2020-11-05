// std::vector<T> for dynamic memory allocation

// solution of homework

#include <iostream>

template<typename T>
struct Vector
{
    int N;
    T* values = nullptr;

    Vector(int N) : N(N), values(new T[N])
    {
        for(auto i=0; i<N; ++i)
            values[i] = 0;
    }

    Vector(const Vector& other) : N(other.N), values(new T[N])
    {
        for(int i=0; i<N; ++i)
            values[i] = other.values[i];
    }

    ~Vector()
    {
        delete[] values;
        values = nullptr; // better safe than sorry
    }

    void operator=(const Vector& other)
    {
        if(N != other.N)
        {
            delete[](values);
            values = new T[other.N];
            N = other.N;
        }
        for(int i=0; i<N; ++i)
            values[i] = other.values[i];
    }

    void set(int index, const T& value)
    {
        values[index] = value;
    }

    auto operator[](int index) const
    {
        return values[index];
    }
};

template<typename T>
void print(const T& t)
{
    std::cout << t << std::endl;
}

template<typename T>
void print(const Vector<T>& v)
{
    for(int i=0; i<v.N; ++i)
        print(v.values[i]);
    std::cout << std::endl;
}

struct Date
{
    int year;
    int month;
    int day;
    Date() : year(0), month(0), day(0) { }
    Date(int year, int month, int day) : year(year), month(month), day(day) { }
    Date(int year, int month) : year(year), month(month), day(0) { }
    Date(int year) : year(year), month(0), day(0) { }
};

void print(const Date& date)
{
    if(date.month != 0 && date.day != 0)
        std::cout << date.year << "-" << date.month << "-" << date.day << std::endl;
    else if(date.month != 0)
        std::cout << "[" << date.year << "-" << date.month << "]" << std::endl;
    else if(date.year)
        std::cout << "(" << date.year << ")" << std::endl;
    else
        std::cout << "<Uninitialized>" << std::endl;
}

int main(int argc, char* argv[])
{
    auto d1 = Date(2012);
    auto d2 = Date(2020, 7);
    auto d3 = Date(2020, 10, 30);
    print(d1);
    print(d2);
    print(d3);

    auto v = Vector<Date>(3);
    print(v);
    v.set(0, d1);
    v.set(1, d2);
    v.set(2, d3);
    print(v);

    auto v_int = Vector<int>(3);
    for(int i=0; i<3; ++i)
        v_int.set(i, i+1);
    print(v_int);

    return 0;
}
