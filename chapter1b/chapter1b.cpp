#include <iostream>
#include "chapter1b.h"

namespace lfcpp
{
    float calculate_avarage(float a, float b)
    {
        float sum = a + b;
        float avg = sum / 2;
        return avg;
    }
}


int main()
{
    std::cout << "Let u examine variables!\n";

    std::cout << "int is...." << sizeof(int) << " bytes long\n";
    std::cout << "short int is...." << sizeof(short int) << " bytes long\n";
    std::cout << "char is..." << sizeof(char) << " bytes long\n";
    std::cout << "bool is..." << sizeof(bool) << " bytes long\n";
    std::cout << "long is..." << sizeof(long) << " bytes long\n";
    std::cout << "long long is." << sizeof(long long) << " bytes long\n";
    std::cout << "long int is." << sizeof(long int) << " bytes long\n";
    std::cout << "float is.." << sizeof(float) << " bytes long\n";
    std::cout << "double is." << sizeof(double) << " bytes long\n";
    std::cout << "long double is." << sizeof(long double) << " bytes long\n";
    std::cout << "int* is..." << sizeof(int*) << " bytes long\n";
    std::cout << "size_t is." << sizeof(size_t) << " bytes long\n";
    std::cout << "__int64 is." << sizeof(__int64) << " bytes long\n";

    float a, b, c;   // first declare some variables
    a = 10;        // assign a value to a
    b = a + 10;    // b is a pplus a constant value
    c = a + b;     // c is the sum of a and b

    std::cout << "average of " << a << " and " << b << " is " << lfcpp::calculate_avarage(a, b) << "\n";


    using namespace lfcpp;
    float fv = calculate_avarage(2.3, 4.5);

    std::cout << "insert a:";     // give the user a hint
    std::cin >> a;                // read the value of a from the keyboard
    std::cout << "input was:" << a << "\n";  // print what the user typed


    return 0;
}
