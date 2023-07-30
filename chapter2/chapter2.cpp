#include <iostream>

int zero_return()
{
    return 0;
}

bool is_valid()
{
    return true;
}

int my_calculation()
{
    return 3;
}

void branching()
{
    std::cout << "branching...\n";

    int a;      // create an integer variable a
    int b;      // create an integer variable b

    std::cout << "insert a:";   // give the user a hint
    std::cin >> a;              // read the value of a from the keyboard
    std::cout << "insert b:";   // another hint for the user
    std::cin >> b;              // now read the value of b

    int c = a + b;   // create an integer variable c and store the sum

    if (c >= 20)      // if c is bigger than or equal to 20
    {
        std::cout << "c is more than 20 : " << c << "\n";   // print this message
    }
    else if (c >= 10) // else if c is bigger than or equal to 10
    {
        std::cout << "c is bigger than or equal to 10 and less than 20 : " << c << "\n";  // print this message
    }
    else             // finally it is less than 10
    {
        std::cout << "c is less than 10 : " << c << "\n";  // print this message
    }

    if (zero_return())
    {
        std::cout << "if you see this message something went wrong\n";
    }

    if (is_valid())
    {
        std::cout << "this is a really valid result\n";
    }

    if (is_valid() && !zero_return())
    {
        std::cout << "is_valid returned true AND negated zero_return was true as well\n";
    }

    // checking for distict values
    // here we assign a random value
    // in real world our variable has a value depending on the program state
    int d = 3;
    switch (my_calculation())
    {
    case 3:
        std::cout << "value of d is 3\n";
        break;
    case 2:
        std::cout << "value of d is 2\n";
        break;
    case 1:
        std::cout << "value of d is 1\n";
        break;
    default:        // in any other case
        std::cout << "value of d is out of limits:" << d << "\n";
        break;
    }
}

void loops()
{
    std::cout << "loops...\n";

    // for
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "for i=" << i << "\n";
    }

    // while
    int i = 0;
    while (i < 5)
    {
        std::cout << "while i=" << i << "\n";
        ++i;
    }

    // do ... while
    i = 5;
    do
    {
        std::cout << "do-while i=" << i << "\n";
        ++i;
    } while (i < 5);

    {
        int sum = 0;
        int i = 1;
        do {
            sum += i;
            ++i;
        } while (i < 10);
    }
    for (;;)
    {
        std::cout << "option 1->5 doubles the input\n";
        std::cout << "option 6->9 does nothing to the input\n";
        std::cout << "option 0 exits\n";
        std::cout << "insert your option:";
        std::cin >> i;
        if (i == 0)
            break;
        if (i > 9)
            continue;
        i = i * 2;
        std::cout << "i=" << i << "\n";
    }

}

void break_and_continue()
{
    {
int sum = 0;
int top_limit = 15;
for (int i = 1; i < 10; ++i)
{
    sum += i;
    if (sum > top_limit)
        break;
}
if (sum > top_limit)
    std::cout << "the sum is greater than " << top_limit << "\n";
else
    std::cout << "the sum is less than or equal to " << top_limit << "\n";
    }

    {
        // count odds only
        int sum = 0;
        for (int i = 1; i < 10; ++i)
        {
            if (i % 2 == 0)  // if we are on an even number
                continue;    // ignore it and go for the next
            sum += i;
        }
        std::cout << "the sum is " << sum << "\n";
    }

}

double f_of_x(double x)
{
    double f = (3 * x * x + 5 * x) / (x + 2);
    return f;
}

double f_of_x_improved(double x)
{
    double f;
    double divisor = x + 2;
    if (divisor != 0)    // check for division by 0
    {
        f = (3 * x * x + 5 * x) / divisor;
    }
    else     // in case of error
    {        // alert the user
        std::cout << "function not defined for x=" << x << "\n";
        f = 0;   // and maybe return some valid value
    }
    return f;
}

double f_of_x_simplified(double x)
{
    double divisor = x + 2;
    if (divisor == 0)    // check for division by 0
    {
        std::cout << "function not defined for x=" << x << "\n";
        return 0;    // return from this point
    }
    return (3 * x * x + 5 * x) / divisor;
}

double calc_average()
{
    double a, sum;                // declare our variables
    sum = 0;                      // initialize the sum
    std::cout << "insert a:";     // give the user a hint
    std::cin >> a;                // read the value of a from the keyboard
    sum = sum + a;
    // ... add more input if needed
    std::cout << "insert a:";     // give the user a hint
    std::cin >> a;                // read the value of a from the keyboard
    sum = sum + a;

    double average = sum / 2;

    return average;
}

int main()
{
    std::cout << "Hello from chapter 2!\n";

    // branching();

    // loops();

    std::cout << "f(1.23)=" << f_of_x_improved(-2) << "\n";

    return 0;
}
