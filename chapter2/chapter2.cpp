#include <iostream>

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

    // checking for distict values
    // here we assign a random value
    // in real world our variable has a value depending on the program state
    int d = 3;
    switch (d)
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

int main()
{
    std::cout << "Hello from chapter 2!\n";

    branching();

    loops();

    return 0;
}
