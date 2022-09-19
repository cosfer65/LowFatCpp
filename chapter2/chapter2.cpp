#include <iostream>

void branching()
{
    int a;      // create an integer variable a
    int b;      // create an integer variable b
    int c;      // create an integer variable c

    std::cout << "insert a:";   // give the user a hint
    std::cin >> a;              // read the value of a from the keyboard
    std::cout << "insert b:";   // another hint for the user
    std::cin >> b;              // now read the value of b

    c = a + b;                  // calculate the value of c

    if (c > 20)      // if c is bigger than 20
    {
        std::cout << "c is more than 20 : " << c << "\n";   // print this message
    }
    else if (c == 20)// else if c is equal to 20)
    {
        std::cout << "c is equal to 20 : " << c << "\n";  // print this message
    }
    else             // else (if c is less than 20)
    {
        std::cout << "c is less than 20 : " << c << "\n";  // print this message
    }

    bool d;         // create a boolean variable
    d = c > 20;     // this will hold weather the condition is true or false
    switch (d)      // depending on the condition do the following
    {
    case true:      // in case it is true
        std::cout << "c is more than 20 : " << c << "\n";   // print this message
        break;
    default:        // in any other case
        std::cout << "c is less or equal to 20 : " << c << "\n";  // print this message
        break;
    }
}

void loops()
{
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
        if (i > 5)
            goto bypass;
        i = i * 2;
    bypass:
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
