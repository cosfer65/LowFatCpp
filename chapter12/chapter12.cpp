// chapter12.cpp
//

#include <iostream>
#include <string>

class my_exception : public std::exception {
public:
    my_exception(const char* msg = "this is a cutom exception") :std::exception(msg) {
    }
};

void throw_some_exception()
{
    throw std::bad_array_new_length();
}

void throw_sample()
{
    std::cout << "throw exception sample\n";
    try
    {
        throw_some_exception();
        // since the previous call raises an exception
        // the next line will not be executed
        std::cout << "this should not be seen\n";
    }
    // catch our custom exception
    catch (my_exception& e)
    {
        std::cout << e.what() << "\n";
    }
    // ignore all other exceptions

    // exception or not the code continues here
    std::cout << "throw exception terminates\n";
}

void higher_sample()
{
    try {
        throw_sample();
    }
    catch (const std::exception& e)
    {
        // the code resumes here after any other exception
        std::cout << "general excption:" << e.what() << "\n";
    }
}

void simple_exception()
{
    std::cout << "simple exception sample\n";
    // we will use this to generate an exception
    int i = -1;
    try
    {
        throw_some_exception();
        // bad allocation exception
        char* buf = new char[i];
        // since the previous line has an error
        // the next line will not be executed
        std::cout << "this should not be seen\n";
    }
    catch (my_exception& e)
    {
        std::cout << e.what() << "\n";
    }
    // catch the bad_array_new_length exception
    catch (const std::bad_array_new_length& e)
    {
        // the code resumes here after the bad_array_new_length exception
        std::cout << "specific exception:" << e.what() << "\n";
    }
    // catch all other exceptions
    catch (const std::exception& e)
    {
        // the code resumes here after any other exception
        std::cout << "general excption:" << e.what() << "\n";
    }

    // exception or not the code continues here
    std::cout << "function terminates\n";
}

int main()
{
    std::cout << "Hello World!\n";

    simple_exception();
    // enabling the following line crashes the program
    // throw_sample();
    higher_sample();

    return 0;
}
