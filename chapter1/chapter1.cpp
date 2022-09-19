#include <iostream>

#include "chapter1.h"

int main()
{
    std::cout << "Hello from chapter1!\n";

    double a, b, c, x;          // here we define some variables

    std::cout << "This program calculates the trinomial a*x*x + b*x + c\n";
    std::cout << "insert a:";   // give the user a hint
    std::cin >> a;              // read the value of a from the keyboard
    std::cout << "insert b:";   // another hint for the user
    std::cin >> b;              // now read the value of b
    std::cout << "insert c:";   // another hint for the user
    std::cin >> c;              // now read the value of c
    std::cout << "insert x:";   // another hint for the user
    std::cin >> x;              // now read the value of x

    double value = gdd::trinomial(a, b, c, x);   // function call

    // output the result
    std::cout << a << "*" << x << "*" << x << " + " << b << "*" << x << " + " << c << " = " << value << "\n";

    return 0;
}

namespace gdd {
    double trinomial(double a, double b, double c, double x)
    {
        double result = a * x * x + b * x + c;
        return result;
    }
}
