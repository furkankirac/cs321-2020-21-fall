// const correctness of a member function (use-case IntVector::print)
// use operator[] for accessing internal values attribute
// use generic programming for creating Vector structs for different primitive types: float, double, short, ...

// overload operator() of IntVector! Transform vector contents

#include <iostream>

// Create an IntVector struct that will support storing N dimensional mathematical vectors of integer numbers.
// The number of dimensions of the vector (N) will be a run-time parameter
//   (You don't know the length of the vector at compile time).
template<typename T>
struct Vector
{
    int N;
    T* values = nullptr;

    // IntVector's constructor must initialize all the values of different dimensions to zero
    //   after allocating necessary space for them.
    Vector(int N) : N(N), values(new T[N])
    {
        for(auto i=0; i<N; ++i)
            values[i] = 0;
    }

    // Write a copy-constructor for IntVector (that can construct a new instance by an already available instance).
    Vector(const Vector& other) : N(other.N), values(new T[N])
    {
        for(int i=0; i<N; ++i)
            values[i] = other.values[i];
    }

    // Write a destructor that frees the allocated memory when the instance is destroyed.
    ~Vector()
    {
        delete[] values;
        values = nullptr; // better safe than sorry
    }

    void print() const
    {
//        auto temp = Vector<T>(5);
//        *this = temp;

        for(int i=0; i<N; ++i)
            std::cout << values[i] << " ";
        std::cout << std::endl;
    }

    // Create a copy-assignment method for IntVector.
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

    // Write a "void set(int index, int value)" method for IntVector struct
    //   that sets the index'th element to value.
    void set(int index, const T& value)
    {
        values[index] = value;
    }

    auto operator[](int index)
    {
        return values[index];
    }

};

// Create a print method for IntVector.
template<typename T>
void print(const Vector<T>& v)
{
//    auto temp = Vector<T>(5);
//    v = temp;

    for(int i=0; i<v.N; ++i)
        std::cout << v.values[i] << " ";
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    // There is a std::cin object meaning console input. Use it for reading an integer from console.
    //   { int N; std::cin >> N; } defines an integer, reads an integer from the keyboard and
    //   stores it in variable "N".
    auto N = 0;
    std::cin >> N;

    // Create an "N" dimensional vector by "IntVector v1(N)" or equivalently "auto v1 = IntVector(N)".
    // If, for instance, N is entered as 5, this creates an IntVector instance that can store 5 different integer values
    //   (use new operator for dynamic memory allocation).
    auto v1 = Vector<int>(N);

    // Use v1.set(...) method for N times via a for loop to
    //   initialize the IntVector instance's contents to 1, 2, ..., N respectively.
    for(int i=0; i<N; ++i)
        v1.set(i, 3.14);

    // Use copy-constructor by "auto v2 = IntVector(v1);"
    auto v2 = Vector<int>(v1);

    // Write v2's contents by "v2.print();" (The output shall be 1, 2, 3, ..., N)
    //   where N is the number entered from the keyboard at program's start.
    v2.print();

    // Create v3 by "auto v3 = IntVector(N);". Print it "v3.print();". Result is "0, 0, ..., 0"
    auto v3 = Vector<int>(N);
    print(v3);

    //"v3 = v1; v3.print();" Result shall be 1, 2, 3, ..., N if you did everything correctly.
    v3 = v1;
    print(v3);

    auto v4 = Vector<double>(N);
    for(int i=0; i<N; ++i)
        v4.set(i, 3.14);
    print(v4);

    auto v5 = Vector<float>(N);
    for(int i=0; i<N; ++i)
        v5.set(i, 3.14f);
    print(v5);

    std::cout << v5[0] << std::endl;

    return 0;
}
