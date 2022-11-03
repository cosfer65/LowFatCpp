// chapter4.cpp
//

#include <iostream>
#include "chapter4b.h"





// user defined callback function that prints even numbers
void my_callback_evens(int v)
{
    // print even numbers
    if ((v % 2) == 0)
        std::cout << v << "\n";
}
// user defined callback function that prints odd numbers
void my_callback_odds(int v)
{
    // print even numbers
    if ((v % 2) == 1)
        std::cout << v << "\n";
}

int main()
{
    std::cout << "Hello from chapter 4!\n";

    // function overloading
    fancy_printer(1);         // calls the first
    double d = 2.75;
    fancy_printer(d);         // calls the second
    char str2[] = "abcd";
    fancy_printer(str2);       // calls the third
    fancy_printer(3, str2);    // calls the fourth

    // default arguments
    std::cout << "with default arguments:" << multiply(2) << "\n";
    std::cout << "with all the arguments:" << multiply(2, 2) << "\n";

    // use pointers to functions
    run_iteration(my_callback_evens);
    run_iteration(my_callback_odds);

    // recursive calls
    std::cout << "factorial of 5 (recursive call):" << recursive_factorial(5) << "\n";
    std::cout << "factorial of 5 (non recursive call):" << factorial(5) << "\n";

    return 0;
}
